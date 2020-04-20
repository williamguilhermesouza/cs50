def count_letters(text):
    counter = 0
    for letter in text.lower():
        if letter >= 'a' and letter <= 'z':
            counter += 1
    return counter


def count_words(text):
    counter = 0
    for i in range(len(text)):
        if text[i] == ' ' and text[i - 1] != ' ':
            counter += 1

    if counter != 0:
        counter += 1

    return counter


def count_sentences(text, word_count):
    counter = 0
    for i in range(len(text)):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            counter += 1

    if counter == 0 and word_count != 0:
        counter += 1

    return counter


def coleman_liau(letter_count, word_count, sentence_count):
    L = letter_count * 100.0 / word_count  # average number of letters per 100 words in the text
    S = sentence_count * 100.0 / word_count  # average number of sentences per 100 words in the text

    index = 0.0588 * L - 0.296 * S - 15.8
    return index


entry = input("Text: ")

letters = count_letters(entry)
words = count_words(entry)
sentences = count_sentences(entry, words)
grade = coleman_liau(letters, words, sentences)

if grade >= 16:
    print("Grade 16+\n")

elif grade < 1:
    print("Before Grade 1\n")

else:
    print(f"Grade {round(grade)}\n")
