require 'colors'

print('booting system')
delay(500)
print('executing ' .. __name__)
delay(500)

display.clear(BLACK)

--print(string.format("display.baseaddr = 0x%x", __display__))

-- draw some stuff on the screen
display.pencolor(GREEN)
display.text(250, 200, "Hello, World!", YELLOW)
display.text(250, 240, "Hello, World!", GREEN)
display.line(20, 180, 620, 180)
display.line(20, 240, 620, 240)

display.pencolor(CYAN)
for x = 20, 620, 5 do
	display.point(x, 100)
end
display.flip()
delay(2000)
print("done.")
