#ifndef CRYPTO_H
#define CRYPTO_H

#include <QtCrypto>

#include "database.hpp"

class Crypto
{
    explicit Crypto(){}
public:
    /**
     * @brief Generate an S_i value for the given index
     * @param ks The client's secret key for S values
     * @param i The index of the S to generate
     *
     * This function generates an S_i value using the secret key ks, and returns it.
     *
     * @return The S value at the given index
     */
    static QCA::SecureArray generateS(QCA::SecureArray ks, DB::Index i);

    /**
     * @brief Generate a k_i value for the given L_i
     * @param kk The client's secret key for k_i values
     * @param Li The L_i value to create a k_i for
     *
     * This function generates a k_i value using the secret key ks and the left section of the pre-encrypted word.
     *
     * @return k_i for L_i using kk
     */
    static QCA::SecureArray generateKi(QCA::SecureArray kk, QCA::SecureArray Li);



    /**
     * @brief Xors the two arrays
     * @param a First array to xor
     * @param b Second array to xor
     *
     * Xors a and b together and returns the result. a and b must be the same length; if they are not, an empty
     * array is returned.
     *
     * @return a ^ b
     */
    static QCA::SecureArray arrayXor(QCA::SecureArray a, QCA::SecureArray b);

    const static quint32 N_BYTES;
    const static quint32 M_BYTES;
};

#endif // CRYPTO_H