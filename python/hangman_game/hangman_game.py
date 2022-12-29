import random
import string

def gameCore(word):
    win = False
    death_count = 6
    letters = []

    stiff = [
               '_', '_', '_' , '_', '_', '\n',
               ' ', 'O', ' ' , ' ', '|', '\n',
               '/', '|', '\\', ' ', '|', '\n',
               '/', ' ', '\\', ' ', '|', '\n',
               ' ', ' ', ' ' , '/', '_', '\\', '\n'
            ]
    clear_stiff = [20, 18, 14, 12, 13, 7]

    while death_count:
        guess = input('Guess your letter: ').capitalize()

        if len(guess) == 1:
            if not guess in string.ascii_uppercase:
                print('Only letters allowed!')
                continue

            if guess in letters:
                print('Letter already inputed!')
                continue

            if guess in word:
                win = True
                letters.append(guess)

                for let in word:
                    if let in letters:
                        print(let, end=' ')
                    else:
                        win = False
                        print('_', end=' ')
                print()
            else:
                death_count -= 1

                temp_stiff = stiff.copy()
                for i in range(death_count):
                    temp_stiff[clear_stiff[i]] = ' '
                print(''.join(temp_stiff))
        if win:
            return True
            
    return False

while True:
    words = []
    with open('sowpods.txt', 'r') as file:
        for line in file:
            words.append(line.strip())

    word = random.choice(words)

    print('Welcome to Hangman!')
    print('-------------------')

    if gameCore(word):
        print("Congratulations! You have guessed the word!")
    else:
        print('You have lost the game!')

    if not input("Would like to start another game? (yes): ") == 'yes':
        break