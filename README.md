![063631dbd777241e0dc40dd2dd17d7cb](https://github.com/user-attachments/assets/896eea04-afe5-4667-bc7d-b83018e0c754)

You can directly run the .exe file. If it doesn't work and you need to compile it. Please use -std=c++11

Input: folding parameter s, list parameter L, word length n, message length k.

Note that the number of column and rows of the matrix can't succeed 5000.

For now, the underlying field is $$\mathbb{F}_{998244353}$$ where 998244353 is a popular prime in programming contest. The generator of the multiplicative group $$\gamma$$ is just $$3$$, which is a primitive root modulo 998244353. You can change it in the code easily.

For the evaluation points, now we just randomly sample a set of distinct evaluation points. You can also make them fixed by modifying the program.

Without loss of generality, in the code we fixed the error set to be [1...e].
