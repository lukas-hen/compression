# compression


## Shannon Entropy
$$
H(X) := -\sum_{x \in X} p(x)log_2(p(x))
$$

## Word Length = Information

For a discrete variable:

$$
I_X(x) := -log_2[p_X(x)]
$$

Where $p_X(x)$ is a discrete pdf.
The information (when the base is 2) gives us the _minumum_ number of binary (yes/no) questions needed to identify the outcome of a random event. This translates to the minimum number of bits required to represent an outcome. As we cannot have fractional bits, we do have to round the information upwards to get the number of bits required for representing each discrete variable.

Given an effective encoding based on these word lengths, we should be able to compress our data to an average number of bits close to the entropy.
