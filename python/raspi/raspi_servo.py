import pygame
import time
import RPi.GPIO as g

joystick_id = 0

g.setmode(g.BCM)
g.setwarnings(False)
g.setup(18, g.OUT)

pwm = g.PWM(18, 50)
dc = 5.5
pwm.start(dc)
# pwm.ChangeDutyCycle(10)

pygame.display.init()
pygame.joystick.init()
pygame.joystick.Joystick(joystick_id).init()

j1 = pygame.joystick.Joystick(joystick_id)
direction = None
try:
    while True:
        pygame.event.pump()

        # Check if direction is indicated
        is_zero = j1.get_axis(2) == 0
        if not is_zero:
            # Check direction (True - right, False - left)
            direction = j1.get_axis(2) > 0
    
            # Get rotation speed
            if j1.get_axis(4) <= 0: speed = 0
            else: speed = j1.get_axis(4)
        
            if direction: dc += speed
            else: dc -= speed
        
            dc = float(format(dc, '.2f'))
            if dc < 1: dc = 1
            elif dc > 10: dc = 10

            pwm.ChangeDutyCycle(dc)
        #print(is_zero, direction, dc)
    
        time.sleep(0.05)
except KeyboardInterrupt:
    pwm.ChangeDutyCycle(0)
    g.cleanup()
    print('Bye :)')
