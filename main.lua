green = 0x00ff00ff
yellow = 0xffff00ff

print("Hello from lua")
print(string.format("display._baseaddr = 0x%x", display._baseaddr))

-- draw some stuff on the screen
display.pencolor(green)
display.text(250, 200, "Hello, World!", yellow)
display.line(20, 180, 620, 180)
display.line(20, 240, 620, 240)
display.flip()
delay(1000)
