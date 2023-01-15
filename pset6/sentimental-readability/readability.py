from cs50 import get_string


def main():
    text = get_string("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    L = (letters / words) * 100
    S = (sentences / words) * 100

    index = 0.0588 * L - 0.296 * S - 15.8
    grade = round(index)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 15:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def count_letters(text):
    total = 0
    for i in range(len(text)):
        if text[i].isalpha():
            total += 1
    return total


def count_words(text):
    total = 1
    for i in range(len(text)):
        if text[i].isspace():
            total += 1
    return total


def count_sentences(text):
    total = 0
    for i in range(len(text)):
        if text[i].isalpha() == 0 and (text[i] == "." or text[i] == "!" or text[i] == "?"):
            total += 1
    return total


main()
