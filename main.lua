require 'colors'

--display.loadfont(1, "fonts/digital/DS-DIGI.TTF", 20)

print("Hello from " .. __name__)
--print(string.format("display.baseaddr = 0x%x", __display__))

-- draw some stuff on the screen
display.pencolor(GREEN)
display.text(250, 200, "Hello, World!", YELLOW)
display.line(20, 180, 620, 180)
display.line(20, 240, 620, 240)

display.pencolor(CYAN)
for x = 20, 620, 5 do
	display.point(x, 100)
end
display.flip()
delay(2000)
