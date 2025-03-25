# Arduino Days 2025 Cotonou at Seme City Open Park

# Challenge 4 : The crypt at forgotten colors

This project is an Arduino-based interactive challenge, where the player must solve a color puzzle to “unlock” an imaginary crypt. Inspired by the concept of a mystical adventure, the system relies on an RGB LED, potentiometer and buttons to generate specific colors and validate a secret sequence.
The project comprises four main modes:
1.	Button or Single mode: Activates red and blue colors independently. When combined, they form purple, symbolizing the opening of the safe.

2.	Mystic Code Mode: The user must reproduce a specific color sequence to unlock the safe (e.g. red, red, blue, red).

3.	Total Arcane mode: control the LED hue with a potentiometer to display all the colors of the rainbow.

4.	Forbidden Enigma mode: the LED flashes in Morse code to guide the user.

# Materials required :
1 Arduino Uno

1 RGB LED (common anode)

3 Pushbuttons (one for red, one for blue and one for mode change)

3 220Ω resistors (to protect the LED)

1 Potentiometer (for Total Arcane mode)

Cables and breadboard

# Wiring diagram : 

![Arduino Days 2025 2](https://github.com/user-attachments/assets/beab9f8b-9c0e-4224-93a7-cc5aac4c67ed)



The RGB LED is connected to the PWM pins for dynamic color adjustment. Pushbuttons are used to select colors.

# Operating modes :
1.	Button mode
Pressing the red button lights up the red LED only.
Pressing the blue button lights up the blue LED only.
Pressing both buttons at the same time lights up the violet color (red + blue).

2.	Mystic Code mode
The user must enter a correct sequence of buttons (ex: red, red, blue, red).
If the sequence is correct, the safe opens (RGB LED lights up purple).
If the sequence is incorrect, the LED does not light up and the sequence is reset.

3.	Total Arcane mode 
The RGB LED displays all the colors of the rainbow, depending on the position of the potentiometer.

4.	Forbidden Enigma mode
The LED flashes Morse code to guide the user.
For example, it may display the letter “...-” for violet.
The mode is determined by the position of the potentiometer or by pressing the green button:
Potentiometer at 0 → Button mode
Potentiometer between 10 and 1000 → Total Arcane mode
Potentiometer at 1000 → Forbidden Enigma mode
Green button pressed → Mystic Code mode

# Possible improvements :
1.	 Guardian of the Lost Lights mode: Add a more complex sequence where several buttons must be pressed in a precise order.
2.	Audio indications: Add a buzzer to indicate errors or successes.
3.	LCD display: Use an LCD screen to guide the user through the active mode and the steps to follow.

# Conclusion
This project offers an interactive and educational experience using RGB LEDs and Arduino inputs. It's perfect for beginners wishing to learn about color management and push-button interaction.
If you take up the challenge and improve the project, please share your results!
