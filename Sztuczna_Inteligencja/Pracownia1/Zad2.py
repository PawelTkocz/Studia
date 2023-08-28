'''
dla każdego wiersza tekstu wywołuję funkcję add_spaces()
Dla każdej litery w wierszu przechowuję w tablicy dwie informacje:
o maksymalnej sumie kwadratów jaką można uzyskać korzystając z
poprzednich liter i długość słowa poprzedzającego tą literę dla 
podziału słów maksymalizujących sumę kwadratów. 
Korzystając z kolejki, rozważam słowa zaczynające się od analizowanej litery
'''

inp = open('zad2_input.txt', 'r')
out = open('zad2_output.txt', 'w')

def init_word_base():
    max_ws = 0
    words_set = {""}
    words = open('polish_words.txt', 'r')
    line = words.readline()
    while line:
        if len(line) - 1>max_ws:
            max_ws = len(line) - 1
        words_set.add(line.strip())
        line = words.readline()
    words.close()
    return (words_set, max_ws)

res = init_word_base()
polish_words = res[0]
max_word_size = res[1]

def add_spaces(line):
    line_len = len(line)
    words_len = [0] * line_len
    words_val = [0] * line_len
    line_len -= 1
    queue = [0]

    while queue:
        i = queue.pop()
        max_len = min(max_word_size, line_len-i)
        word = ""
        for j in range(max_len):
            word += line[i+j]
            if word in polish_words:
                new_val = words_val[i] + (j+1)*(j+1)
                if new_val > words_val[i+j+1]:
                    words_val[i+j+1] = new_val
                    words_len[i+j+1] = j+1
                    queue.append(i+j+1)

    spaces = []
    nwords = 0
    i = line_len
    while(i>0):
        spaces.append(words_len[i])
        nwords += 1
        i -= words_len[i]

    for j in range(nwords):
        ws = spaces[nwords-1-j]
        for k in range(ws):
            out.write(line[i+k])
        out.write(" ")
        i += ws
    out.write("\n")


line =  inp.readline()
while line:
    add_spaces(line)
    line = inp.readline()
inp.close()
out.close()