# VirtualWashingMachine
Motor1 simulates the drum of the washing machine. It should rotate whenever the machine is washing,
rinsing or centrifuging. Otherwise it should be stopped.
Motor2 simulates the water pump of the washing machine. It should rotate whenever water is pumped out of
the machine. Otherwise it should be stopped.
Switch1 is turning the machine ON/OFF
Switch2 simulates the sensor which is ‘1’ whenever there is enough water in the machine.
Switch3 simulates the sensor which is ‘1’ whenever all the water is pumped out of the machine.
Relay is ON when the machine takes water.
The routine of the washing machine goes like this:
1. Washing machine takes water about 3 s.
2. Washing machine is washing 9 s. (The speed of the motor should be moderate)
3. Dirty water is pumped out of the machine about 3 s.
4. Washing machine takes water about 3 s.
5. Washing machine is rinsing 5 s.
6. Rinsing water is pumped out of the machine about 3 s.
7. Washing machine is centrifuging 5 s. (The speed of the motor should be high)
8. Led is Blinking when the washing program is finished.
9. Washing machine can be turned OFF
