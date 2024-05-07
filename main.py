import gpsd
from time import sleep
import os 
import renderizar_frame as frame
import threading

VELOCIDADE_LIMITE = 95
TEMPO_DELAY = 0.2

frame.boot_guru()
while True:
    try:
        

        # Configuracao padrao de porta
        gpsd.connect(host="127.0.0.1", port=2947)

        while True:
            
            dados_gps = gpsd.get_current()
            
            modo_gps = dados_gps.mode
            numero_satelites_encontrados = dados_gps.sats 
            
            # <  1 NO MODE
            # == 1 NO FIX
            # == 2 2D FIX
            # >= 3 3D FIX
            if modo_gps >= 2:
                
                mapa_url = dados_gps.map_url()
                latitude = dados_gps.lat
                longitude = dados_gps.lon
                # Convertendo velocidade de metros por segundo para kmp/h
                velocidade_kmp = round(dados_gps.hspeed * 3.6)
                
                #print(mapa_url)
                print(f"{velocidade_kmp} KM/h")
                threading.Thread(target=frame.mostrar_velocidade,args=(velocidade_kmp,)).start() 
                print(latitude,longitude)
                TEMPO_DELAY = 0.2
            else:
                TEMPO_DELAY = 1
                threading.Thread(target=frame.sem_sinal_gps, daemon=False).start()
                
            sleep(TEMPO_DELAY)
            
    except ConnectionRefusedError:    
        print("Conexao falhou... servidor local possivelmente fechado!")
        ip_local = os.system("hostname -I")
        os.system(f"gpsd -N udp://{ip_local}:8080 &")
        frame.mensagem_boot("Iniciando servidor")
        frame.animacao_carregamento()
    except UserWarning as erro:
        print("SINAL GPS NAO ENCONTRADO: --> ", erro)
        frame.mensagem_boot("Aguardando GPS")
        frame.animacao_carregamento()

    except Exception as erro:
        print("ERRO DESCONHECIDO: ", erro)
