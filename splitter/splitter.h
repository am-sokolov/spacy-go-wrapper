// sentence_splitter.h
#ifndef SENTENCE_SPLITTER_H
#define SENTENCE_SPLITTER_H

#ifdef __cplusplus
extern "C" {
#endif

void initialize_spacy();
char** split_sentences(const char* text, int* num_sentences);
void free_sentences(char** sentences, int num_sentences);
void finalize_spacy();

#ifdef __cplusplus
}
#endif

#endif // SENTENCE_SPLITTER_H

