# Dungeon: You vs THE WORLD 🎲🔐

## 📖 Description
Dungeon: You vs THE WORLD is a two-player text-based game written in C.  
You (Player 1) face off against Bob (the CPU). Each round, both roll two dice.  
- If your roll sum is lower, you gain a letter from a secret word.  
- If your roll is the highest possible, you lose a letter.  
The game continues until one player collects all five letters of the random word, becoming the loser.  
The losing player's word is then encrypted using a Caesar Cipher with their dice roll sum as the shift key.

---

## ⚙️ Prerequisites
- **OS**: Linux or Windows (must support C compilation)  
- **Compiler**: `gcc` (GNU Compiler Collection)  
- **Make**: Ensure `make` is installed for using the provided Makefile  

---

## 🛠️ Installation & Build
1. Clone or download the project folder.  
2. Open a terminal inside the project directory.  
3. Run the following command to build the program:

```bash
make
```

This will generate an executable (e.g., `cubic_dungeon`).  

To clean up the compiled files, run:

```bash
make clean
```

---

## ▶️ How to Use
1. Run the program in terminal:

```bash
./cubic_dungeon
```

2. Enter the following inputs as prompted:  
   - **Seed Value**: A number between `1` and `9999`.  
   - **Player Name**: Between 2-8 alphabetic characters.  
   - **Dice Sides**: In the format `#x#` (each side between 1-5).  

3. Play the game and watch as dice rolls decide the outcome.  
4. At the end, the loser's word is displayed in encrypted form.  

---

## 🧾 Sample Run

```text
Please input a seed from [1-9999] (Has to be a number): 123
>* Alright! Now that we have the seed, this will be the generated word for the game!
| Word of the Game: rlpal

Please enter your name: Sam
Please input your sides in the form of "#x#": 3x3

Round 1 starting now!
- Sam rolled a 4
- Bob rolled a 5

Sam's word is: r
Bob's word is: 

...
Sam has lost the game!
Their encrypted word is: eifns
```

---

✨ Have fun escaping the dungeon... or encrypting your fate!  
