import cs50


def main():
    text = cs50.get_string("Insert text:\n")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    letters = letters / words
    letters = letters * 100
    sentences = sentences / words
    sentences = sentences * 100
    index = (0.0588 * letters - 0.296 * sentences) - 15.8

    #print(f"Grade {index}")
    index = round(index)
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    letters = 0
    i = 0
    str_len = len(text)

    for i in range(str_len):

        if (ord(text[i]) < 65 or ord(text[i]) > 90) and (ord(text[i]) < 97 or ord(text[i]) > 122):
            continue
        letters = letters + 1

    return letters


def count_words(text):
    words = 0
    i = 0
    str_len = len(text)

    for i in range(str_len):
        if text[i] == ' ':
            words = words + 1

    words = words + 1  # There is one space less

    return words


def count_sentences(text):
    sentences = 0
    i = 0
    str_len = len(text)

    for i in range(str_len):

        if text[i] == '!' or text[i] == '?':
            sentences = sentences + 1

        if text[i] == '.':
            if (i + 1) != str_len and text[i + 1] == '.':
                continue
            sentences = sentences + 1

    return sentences


main()

