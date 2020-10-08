Windows10, g++ version 8.1.0

*Card Info: [Shape][Number]
	S: Spade, D: Diamond, C: Clover, H: Heart
	ex. [C][8]: Clover 8

* if card is hidden: [-][-] is shown

* playPile0 ~ 6: playingPiles

* outPile 0 ~ 3: OutPut Piles

* Order in cardPile: bottom -> top

* example) playPile4: [-][-], [C][9], [D][10] means
there are three cards, hidden, Clover 9, Diamond 10 in playPile4,
and Diamond 10 is on the top of the stack(cardPile)

*CardMove: [Shape][Number]: Previous cardpile -> next cardpile
example) [C][8]: PlayPile5 -> PlayPile0 means
Card Clover 8 is moved from PlayPile5 to PlayPile0

