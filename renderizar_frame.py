import time
import board
import busio
import digitalio
import threading
from PIL import Image, ImageDraw, ImageFont
import adafruit_ssd1306
import subprocess
import os
import random


#Definindo paramentros do display
WIDTH = 128 
HEIGHT = 64
BORDER = 5

oled_reset = digitalio.DigitalInOut(board.D4)

i2c = board.I2C()

oled = adafruit_ssd1306.SSD1306_I2C(WIDTH, HEIGHT, i2c, addr=0x3C, reset=oled_reset)


#Criando um imagem em branco (1 bit para exibir no display).
image = Image.new("1", (oled.width, oled.height))

#Criando objeto para desenhar no display
#Seguindo documentacao PIL
draw = ImageDraw.Draw(image)

#draw.rectangle((0, 0, oled.width, oled.height), outline=255, fill=255)

# Definindo fontes para criacao dos frames
fonte_texto = ImageFont.truetype('fontes/pixeloperator.ttf', 50)
fonte_icone = ImageFont.truetype('fontes/lineawesome-webfont.ttf', 20)

def limpar_display(oled) -> None:
    oled.fill(0)
    oled.show()

def sem_sinal_gps() -> None:
    
    # Icone radar
    draw.text((105, 5),  chr(63424), font=fonte_icone, fill=255)

    oled.image(image)
    oled.show()
    time.sleep(0.5)


    # Criando um retangulo preto para apagar icone gps
    draw.rectangle((130, 3, 105, 25), outline=0, fill=0)

    oled.image(image)
    oled.show()
        
    time.sleep(0.4)
        
        

def mostrar_velocidade(velocidade=0):

    # Mostrando retangulo em branco com o tamnhao da tela para apagar frame anterior 
    draw.rectangle((0, 0, oled.width, oled.height), outline=0, fill=0)
    
    draw.text((0, 0),  f"{velocidade} KM", font=fonte_texto, fill=255)
    oled.image(image)
    oled.show()


def boot_guru() -> None:
    nome = "Radar Guru_"
    nome_lista = []
    
    fonte_boot_texto = ImageFont.truetype('fontes/pixeloperator.ttf', 30)
    fonte_boot_icone = ImageFont.truetype('fontes/la-brands-400.ttf', 31)
    
    icone_rasp = 63419
    icone_python = 62434

    for letra in nome:

        # Se proxima letra for um Espaco
        if letra == " ":
            nome_lista.append(letra)
            continue
        
        draw.text((0,10), f"{''.join(nome_lista)}", font=fonte_boot_texto, fill=255)
        nome_lista.append(letra) 
        
        #Mostrando image
        oled.image(image)
        oled.show()

    #draw.text((50,31), chr(icone_python), font=fonte_boot_icone, fill=255)    
    oled.image(image)
    oled.show()

def mensagem_boot(mensagem) -> None:
   
    draw.rectangle((0, 44, 103, 50), outline=0, fill=0)
    
    fonte_texto = ImageFont.truetype('fontes/pixeloperator.ttf', 12)
    #draw.rectangle((0, 0, oled.width, oled.height), outline=0, fill=0)
    draw.text((0,40), f"{mensagem}", font=fonte_texto, fill=255)
    oled.image(image)
    oled.show()

def carregar_frame(mensagem,limpar=False):
    
    if limpar:
        draw.rectangle((0, 0, oled.width, oled.height), outline=0, fill=0)

    
    fonte_texto = ImageFont.truetype('fontes/pixeloperator.ttf', 12)
    draw.text((0,40), mensagem, font=fonte_texto, fill=255)
    
    draw.rectangle((0, 44, 103, 50), outline=255, fill=255)

    oled.image(image)
    oled.show()
    

def animacao_carregamento():
    carregamento = [n for n in "." * 3]
    
    xl = 97
    for x in carregamento:
        fonte_texto = ImageFont.truetype('fontes/pixeloperator.ttf', 49)
        draw.text((xl,10), x, font=fonte_texto, fill=255)
        oled.image(image)
        oled.show()

        xl += 5
        time.sleep(0.5)

    draw.rectangle((119, 47, 103, 50), outline=0, fill=0)
    oled.image(image)
    oled.show()
