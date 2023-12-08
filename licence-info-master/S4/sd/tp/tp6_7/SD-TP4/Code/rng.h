#ifndef __RNG_H__
#define __RNG_H__

/**
 *	@defgroup DISCRNG Re-entrant random number generator.
 *	@brief Discrete random numbers generator for skip-lists.
 *
 *	Generates discrete random numbers following the probability law described in rng_get_value()
 *  @see rng_get_value()
 *  @{
 */

/**
 * @brief Random number generator parameters.
 * In order to generate reproducible sequences of random numbers, this structure manages the seed of the sequence that will be updated at each new generated number.
 */
typedef struct s_rng_ {
	/// seed parameters.
	unsigned short xsubi[3];
} RNG;

/**
 * @brief Initialize the random sequence at the given seed
 * @param seed is at least a 64 bits unsigned integer
 */
RNG rng_initialize(unsigned long long int seed);

/**
 * @brief Generate a new value in the range [0..max_value].
 * Values are generated such that they follow the discrete probability law defined by :
 * @par 
 * \f$ (0 \le i < max\_value) \rightarrow P(i) = \frac{1}{2^{i+1}} \f$ \n
 *      \f$ p(max\_value) = \frac{1}{2^{max\_value}} \f$
 *
 * @param rng : the seed describing the sequence.
 * @param max_value : the upper bound of the generated values
 * @return the generated number.
 */
unsigned int rng_get_value(RNG *rng, unsigned int max_value);

/** @} */
#endif
