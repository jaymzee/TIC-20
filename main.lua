require 'colors'

--display.text(10,10, "hey", RED)
--display.clear(BLUE)
display.text(250, 240, "one", YELLOW)
display.flip()

delay(1000)

--display.clear(BROWN)
display.text(250, 240, "two", YELLOW)
display.flip()

delay(1000)

display.text(250, 240, "three", GREEN)
display.flip()

delay(1000)

display.clear(RED)
display.flip()

delay(1000)

print("Hello from " .. __name__)

delay(1000)
--print(string.format("display.baseaddr = 0x%x", __display__))

-- draw some stuff on the screen
display.pencolor(GREEN)
display.text(250, 200, "Hello, World!", YELLOW)
display.text(250, 240, "Hello, World!", BLUE)
display.line(20, 180, 620, 180)
display.line(20, 240, 620, 240)
display.flip()

delay(1000)

display.pencolor(CYAN)
for x = 20, 620, 5 do
	display.point(x, 100)
end
display.flip()
delay(2000)
print("done.")
