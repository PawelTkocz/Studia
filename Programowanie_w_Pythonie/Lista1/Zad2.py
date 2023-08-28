def prepare_text(text):
    #funkcja usuwa z tekstu wszystkie znaki niebędące literami
    #dodatkowo wszystkie duże litery zmiania w małe
    text = text.lower()
    letters = []
    for char in text:
        if char.isalpha():
            letters.append(char)
    return letters

def is_palindrom(text):
    text = prepare_text(text)
    for i in range(len(text)//2):
        if text[i] != text[-1 - i]:
            return False
    return True

text1 = 'rotor'
text2 = 'Kapas'
text3 = 'Kobyła ma mały bok.'
text4 = 'Pap lar ral papa'
text5 = 'Eine güldne, gute Tugend: Lüge nie!'
text6 = 'Kajakk'
text7 = 'Míč omočím.'

print(text1 + " " + str(is_palindrom(text1)))
print(text2 + " " + str(is_palindrom(text2)))
print(text3 + " " + str(is_palindrom(text3)))
print(text4 + " " + str(is_palindrom(text4)))
print(text5 + " " + str(is_palindrom(text5)))
print(text6 + " " + str(is_palindrom(text6)))
print(text7 + " " + str(is_palindrom(text7)))
