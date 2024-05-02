This is my README file for HW 5

When creating players, once the final person has been created, press the enter key and the game will start.
You can keep playing the game as long as you want until you end "n" when asked if you want to play again.
There is a new deck created for each game, so you will not run out of cards.



I created a blackjack game with 2 added specail cards 
- Joker Card: This card can be used as any card in the deck, 1-11
- Emporer Card: This card has 2 options:
    - The player may choose to take one of the dealer's cards and add it to their hand
    - The player may choose to just take a card from the deck

I have the game creating:
- A deck of cards 52 standard cards
- 4 * num of players special cards: If you want more or less they are created on line 83 in the AddSpecialCards function
        If you would like more Ace cards to see their functionality, there is a commented out for loop inside of the function that will add more Ace cards to the deck
- A dealer



The game is won by:
- The dealer if:
    - All the players bust
    - The dealer has a higher score than the player

- The player if:
    - The dealer busts
    - The player has a higher score than the dealer

All the players who do not bust and have a higher score than the dealer win
All the players who do not bust and the dealer busts win

The dealer will hit until they have a score of 17 or higher
They do not get to use the special cards. They are equivalent to 0 for the dealer

to Replace the graphical emelement i applied static analysis to the code.
I used CPPCheck to analyze the code and find any errors or warnings that may be present in the code.

The errors/warnings that were found are in a text file called "cppcheck.txt" in the root directory of the project.

I fixed all of the warnings that i found that were applicable. Most of them were not very helpful, but it turns out for a lot of my child classes i had been overriting or not using the parent class's functions. I fixed this by removing the child class's function and using the parent class's function instead.
I had also been creating variables i did not need to a lot. 
I had also functions that were using more memory than they needed to. There was excess variable creating, list creation, and function calls that were not needed. I removed these to make the code more efficient.
I had extra functions that i did not even use. 
I added checks for for loops that might not end or could grow too big

