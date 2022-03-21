# TODO
def main():
    text = input("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    L = letters * 100 / words
    S = sentences * 100 / words

    index = 0.0588 * L - 0.296 * S - 15.8
    print(f"Grade: {round(index)}")

def count_letters(text):
    count = 0
    for letter in text:
        if letter.isalpha():
            count += 1
    return count

def count_words(text):
    count = 0
    for letter in text:
        if letter == " ":
            count += 1
    count += 1
    return count

def count_sentences(text):
    count = 0
    for letter in text:
        if letter in [".", "!", "?"]:
            count += 1
    return count


if __name__ == "__main__":
    main()