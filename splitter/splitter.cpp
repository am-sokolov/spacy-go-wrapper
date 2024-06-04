#include "splitter.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <spacy/spacy>
//#include <spacy/spacy.h>
//#include <spacy/nlp.h>
//#include <spacy/doc.h>
//#include <spacy/span.h>
#include <Python.h>

Spacy::Spacy spacy;
Spacy::Nlp* nlp = nullptr;

extern "C" void initialize_spacy() {
    if (!Py_IsInitialized()) {
        Py_Initialize();
//        std::cout << "Python interpreter initialized" << std::endl;
    }

    if (!nlp) {
        nlp = new Spacy::Nlp(spacy.load("en_core_web_sm"));
        if (!nlp) {
            throw std::runtime_error("Failed to load spaCy model.");
        }
//        std::cout << "SpaCy model initialized successfully" << std::endl;
    }
}

extern "C" char** split_sentences(const char* text, int* num_sentences) {
    if (!nlp) {
        throw std::runtime_error("NLP model not initialized. Call initialize_spacy() first.");
    }

    // Acquire the Python GIL
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

//    std::cout << "Parsing text" << std::endl;
    auto doc = nlp->parse(text);

    std::vector<std::string> sentences;
    for (auto& sent : doc.sents()) {
        sentences.push_back(sent.text());
    }

    *num_sentences = sentences.size();
    char** result = new char*[*num_sentences];
    for (int i = 0; i < *num_sentences; ++i) {
        result[i] = new char[sentences[i].size() + 1];
        std::strcpy(result[i], sentences[i].c_str());
    }

//    std::cout << "Split sentences successfully" << std::endl;

    // Release the Python GIL
    PyGILState_Release(gstate);

    return result;
}


extern "C" void free_sentences(char** sentences, int num_sentences) {
//    std::cout << "Freeing sentences" << std::endl;
    for (int i = 0; i < num_sentences; ++i) {
        delete[] sentences[i];
    }
    delete[] sentences;
//    std::cout << "Sentences freed successfully" << std::endl;
}

extern "C" void finalize_spacy() {
    if (nlp) {
        delete nlp;
        nlp = nullptr;
//        std::cout << "SpaCy model finalized" << std::endl;
    }
    if (Py_IsInitialized()) {
        Py_Finalize();
//        std::cout << "Python interpreter finalized" << std::endl;
    }
}