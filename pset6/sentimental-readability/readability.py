# Author: Marko Solajic

from cs50 import get_string


def main():
    text = get_string("Text: ")

    # Counting number of words, letters and sentences
    words, words_list = count_words(text)
    letters = count_letters(text, words_list)
    sentences = count_sentences(text)

    # Average num of letters per 100 words
    L = (letters / words) * 100

    # Average num of sentences per 100 words
    S = (sentences / words) * 100

    # Coleman-Liau index
    index = 0.0588 * L - 0.296 * S - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


def count_words(text):
    words_list = text.split()
    words_num = len(words_list)
    return (words_num, words_list)


def count_letters(text, words_list):
    letters_num = 0
    for word in words_list:
        for letter in word:
            if letter.isalpha():
                letters_num += 1
    return letters_num


def count_sentences(text):
    sentences_num = 0
    for char in text:
        if char in ".!?":
            sentences_num += 1
    return sentences_num


if __name__ == "__main__":
    main()
