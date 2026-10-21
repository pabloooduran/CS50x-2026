text = input("Text: ")
letter_count = sum(c.isalpha() for c in text)
word_count = 1 + sum(c == ' ' for c in text)
sentence_count = sum(c in ".!?!" for c in text)
L = (letter_count / word_count) * 100
S = (sentence_count / word_count) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print("Grade", index)
