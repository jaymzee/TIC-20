require 'colors'

display.loadfont(1, "fonts/digital/DS-DIGI.TTF", 20)

print("Hello from " .. __name__)
--print(string.format("display.baseaddr = 0x%x", __display__))

-- draw some stuff on the screen
display.pencolor(GREEN)
display.text(250, 200, "Hello, World!", YELLOW)
display.text(250, 220, "Hello, World!", YELLOW, 1)
display.line(20, 180, 620, 180)
display.line(20, 240, 620, 240)
display.flip()
delay(2000)
