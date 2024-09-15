import _thread
from machine import Pin, SPI
from utime import sleep_ms
from lcd12864 import LCD12864
from faces import Faces
import framebuf
import stepper

# Define the stepper motor pins
IN1 = 9
IN2 = 10
IN3 = 11
IN4 = 12

def main_display():
    spi = SPI(1, baudrate=1_000_000, sck=Pin(14), mosi=Pin(15))
    cs = Pin(13, Pin.OUT, value=0)
    fbuf = LCD12864(spi, cs)
    print(fbuf._spi)
    fbuf.fill(0)
    
    calm = framebuf.FrameBuffer(Faces.calm, 128, 64, framebuf.MONO_HMSB)
    blink = framebuf.FrameBuffer(Faces.blink, 128, 64, framebuf.MONO_HMSB)


    # f = framebuf.FrameBuffer(buffer, 128, 64, framebuf.MONO_HLSB)
    while(True):
        fbuf.blit(calm, 0, 0)
        fbuf.show()
        sleep_ms(2000)
        fbuf.blit(blink, 0, 0)
        fbuf.show()
        sleep_ms(500)

def main_motor():
    # Initialize the stepper motor
    stepper_motor = stepper.HalfStepMotor.frompins(IN1, IN2, IN3, IN4)

    # Set the current position as position 0
    stepper_motor.reset()
    
    while True:
        stepper_motor.step(-200)
        sleep_ms(1000)
        stepper_motor.step(200)
        sleep_ms(1000)
        

if __name__ == '__main__':
    
    _thread.start_new_thread(main_motor, ())
    main_display()

    