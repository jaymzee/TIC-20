require 'colors'

print("Hello from " .. __name__)
--print(string.format("display._baseaddr = 0x%x", display._baseaddr))

-- draw some stuff on the screen
display.pencolor(GREEN)
display.text(250, 200, "Hello, World!", YELLOW)
display.line(20, 180, 620, 180)
display.line(20, 240, 620, 240)
display.flip()
delay(2000)
