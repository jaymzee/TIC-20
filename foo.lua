green = 0x00ff00ff
yellow = 0xffff00ff
black = 0x000000ff
fps = 30

print("Hello from lua")

pencolor(0x0000ff80)
for x = 1, 120 do
	clear(black)
	text(50, 50, "Hello, World!", yellow)
	line(10 + x, 40, 200, 100)
	flip()
	delay(1000 / 30)
end
