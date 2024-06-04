package splitter

/*
#cgo pkg-config: python3
#cgo CXXFLAGS: -std=c++11
#cgo LDFLAGS: -L/usr/local/lib -lstdc++ -lspacy -lpython3.10
#include <stdlib.h>
#include "splitter.h"
*/
import "C"
import (
	"runtime"
	"unsafe"
)

func init() {
	C.initialize_spacy()
	runtime.LockOSThread()
}

func Finalize() {
	C.finalize_spacy()
	runtime.UnlockOSThread()
}

func SplitSentences(text string) []string {
	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	var numSentences C.int
	cSentences := C.split_sentences(cText, &numSentences)
	defer C.free_sentences(cSentences, numSentences)

	num := int(numSentences)
	sentences := make([]string, num)
	for i := 0; i < num; i++ {
		cSentence := C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(cSentences)) + uintptr(i)*unsafe.Sizeof(*cSentences))))
		sentences[i] = cSentence
	}
	return sentences
}
