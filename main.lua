green = 0x00ff00ff
yellow = 0xffff00ff

print("Hello from lua")
pencolor(green)
line(10, 40, 200, 100)
text(50, 50, "Hello, World!", yellow)
flip()
delay(1000)
