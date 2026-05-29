# Capillary Suction Timer (CST)

**Hardware build in progress — documentation added ahead of completion.**

Built for a Karachi-based engineering startup [ogengg.com](https://ogengg.com/) as a low-cost alternative to commercial CST instruments. Commercial units from companies like OFITE typically cost $500–$1,500 USD — this builds a functional equivalent for under $35.

## What is this device and what does it do

A Capillary Suction Timer is an instrument that measures how easily liquid can be squeezed out of a wet sludge or mud sample. You place a small sludge sample into a cylindrical reservoir sitting on top of a piece of filter paper. The liquid naturally wicks outward through the paper by capillary action. Three metal electrode pins are embedded in the block at precise distances from the reservoir. When the liquid reaches the first two inner pins, a timer starts automatically. When the liquid reaches the outer pin, the timer stops. The result — displayed in seconds on an LCD screen — is the Capillary Suction Time (CST) value. A lower number means the sludge dewaters easily. A higher number means it doesn't.

## Why is it needed

Industries like wastewater treatment, oil drilling, and water utilities need to know how well their sludge or mud samples dewater before running them through expensive filtration equipment. Without a CST measurement, operators are guessing. Commercial CST devices from companies like OFITE cost hundreds of dollars. This project builds a fully functional equivalent for under $35 using an Arduino Nano and basic components.

## Components used

- Arduino Nano (ATmega328P)
- 16x2 LCD display with I2C backpack module
- 3 stainless steel electrode pins embedded in an acrylic block
- Whatman Grade 17 chromatography filter paper
- Machined acrylic upper block with cylindrical sample reservoir
- Machined acrylic lower block (base plate)
- Stainless steel guide rods
- Momentary push button (reset)
- Perfboard for permanent circuit
- 5V USB power supply

## How it works

The Arduino uses INPUT_PULLUP on three digital pins connected to the three electrode pins. When the filter paper is dry, all pins read HIGH. As liquid from the sludge sample wicks outward through the paper, it bridges the two inner electrode pins first — both drop LOW — and the Arduino starts counting milliseconds. When the liquid continues wicking outward and reaches the outer electrode pin, it drops LOW and the Arduino stops the timer. The elapsed time is displayed on the LCD to two decimal places in seconds. A reset button clears the display and readies the device for the next test.

## Challenges I ran into

The biggest challenge was understanding electrode detection. I initially wired all electrode pins to a shared ground on the breadboard which caused the timer to trigger instantly at 0.9 seconds every time — before any sample was even added. The fix was realizing that only one pin should connect to GND (the inner pin 1 acts as the ground reference), and the liquid itself completes the circuit between the pins. Plain tap water also did not conduct well enough during testing — adding salt to the test water fixed the conductivity issue during development. Getting the LCD to display anything was also tricky at first until I found that the contrast potentiometer on the I2C backpack just needed to be adjusted with a small screwdriver.
