import random

figurant_talia = []
blotkarz_talia = []
#kolory: 0, 1, 2, 3
figury = ['j', 'q', 'k', 'a']
blotki = [i for i in range(2, 11, 1)]
random.seed()

for i in range(4):
    for j in range(len(figury)):
        figurant_talia.append((figury[j], i))
    for j in range(len(blotki)):
        blotkarz_talia.append((blotki[j], i))

def losuj_figurant():
    cards = []
    for i in range(5):
        card = random.choice(figurant_talia)
        cards.append(card)
        figurant_talia.remove(card)
    for i in range(5):
        figurant_talia.append(cards[i])
    return cards

def losuj_blotkarz():
    cards = []
    for i in range(5):
        card = random.choice(blotkarz_talia)
        cards.append(card)
        blotkarz_talia.remove(card)
    for i in range(5):
        blotkarz_talia.append(cards[i])
    return cards

def card_value(card):
    return card[0]

def kolor(cards):
    #tylko blotkarz może miec kolor
    c1, c2, c3, c4, c5 = cards[0][1], cards[1][1], cards[2][1], cards[3][1], cards[4][1]
    return c1==c2 and c2==c3 and c3==c4 and c4==c5

def strit(cards):
    #tylko blotkarz może mieć strita
    cards.sort(key=card_value)
    f1, f2, f3, f4, f5 = cards[0][0], cards[1][0], cards[2][0], cards[3][0], cards[4][0]
    return f1 == f2-1 and f2 == f3-1 and f3==f4-1 and f4==f5-1

def kareta(cards):
    cards.sort(key=card_value)
    f1, f2, f3, f4, f5 = cards[0][0], cards[1][0], cards[2][0], cards[3][0], cards[4][0]
    if f1 == f2:       
        return f1 == f2 and f2 == f3 and f3 == f4
    else:
        return f2 == f3 and f3 == f4 and f4 == f5

def full(cards):
    cards.sort(key=card_value)
    f1, f2, f3, f4, f5 = cards[0][0], cards[1][0], cards[2][0], cards[3][0], cards[4][0]
    if f2 == f3:       
        return f1 == f2 and f2 == f3 and f4 == f5
    else:
        return f1 == f2 and f3 == f4 and f4 == f5

def trojka(cards):
    cards.sort(key=card_value)
    m = 1
    prev = cards[0][0]
    for i in range(1, 5, 1):
        if cards[i][0] == prev:
            m += 1
        else:
            if m == 3:
                return True
            prev = cards[i][0]
            m = 1
    return m == 3

def dwie_pary(cards):
    cards.sort(key=card_value)
    m = 1
    pairs = 0
    prev = cards[0][0]
    for i in range(1, 5, 1):
        if cards[i][0] == prev:
            m += 1
        else:
            if m == 2:
                pairs += 1
            prev = cards[i][0]
            m = 1
    if m==2:
        pairs += 1
    return pairs == 2

def para(cards):
    cards.sort(key=card_value)
    prev = cards[0][0]
    for i in range(1, 5, 1):
        if cards[i][0] == prev:
            return True
        else:
            prev = cards[i][0]
    return False

def winner(figurant, blotkarz):
    bl_color = kolor(blotkarz)
    bl_strit = strit(blotkarz)

    #poker
    if bl_color and bl_strit:
        return 'B'
    #kareta
    if kareta(figurant):
        return 'F'
    elif kareta(blotkarz):
        return 'B'
    #full
    if full(figurant):
        return 'F'
    elif full(blotkarz):
        return 'B'
    #kolor
    if bl_color:
        return 'B'
    #strit
    if bl_strit:
        return 'B'
    #trojka
    if trojka(figurant):
        return 'F'
    elif trojka(blotkarz):
        return 'B'
    #dwie pary
    if dwie_pary(figurant):
        return 'F'
    elif dwie_pary(blotkarz):
        return 'B'
    #para
    if para(figurant):
        return 'F'
    elif para(blotkarz):
        return 'B'
    #wysoka karta
    return 'F'

ntests = 100000
nblot = 0
for i in range(ntests):
    win = winner(losuj_figurant(), losuj_blotkarz())
    if win == 'B':
        nblot += 1
print(nblot/ntests*100)





