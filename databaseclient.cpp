#include <QDebug>

#include "databaseclient.hpp"

#include "crypto.hpp"

QCA::SecureArray DatabaseClient::generateTi(DB::Word word, DB::Index index)
{
    QCA::SecureArray ti = Crypto::generateS(ks, index);
    ti.append(Crypto::generateFki(Crypto::generateKi(kk, word.left(Crypto::N_BYTES - Crypto::M_BYTES)), ti));
    return ti;
}

DatabaseClient::DatabaseClient(QObject *parent) :
    QObject(parent),
    kPrime(QCA::Random::randomArray(16)),
    preEncryptIV(QCA::Random::randomArray(16)),
    ks(QCA::Random::randomArray(16)),
    kk(QCA::Random::randomArray(16))
{
}

DB::RowList DatabaseClient::encryptNewRows(DB::RowList newRows, DB::Index nextAvailableIndex)
{
    DB::RowList crypticRows;

    foreach (DB::Row row, newRows) {
        crypticRows.append(DB::Row());
        for (int c = 0; c != DB::EndColumns; ++c) {
            DB::Word word = Crypto::preEncrypt(row[c], kPrimePrime.derivePublicKey());

            if (DB::ComputableColumns.contains(DB::Columns(c))) {
                crypticRows.last().append(word);
            } else {
                QCA::SecureArray ti = generateTi(word, nextAvailableIndex++);
                crypticRows.last().append(Crypto::arrayXor(word, ti).toByteArray());
            }
        }
    }

    return crypticRows;
}

DB::RowList DatabaseClient::decryptRows(DB::IndexedRowList crypticRows)
{
    DB::RowList plaintextRows;

    foreach(DB::IndexedRow row, crypticRows) {
        quint32 index = row.first;
        plaintextRows.append(DB::Row());
        for (int c = 0; c != DB::EndColumns; ++c) {
            DB::Word crypticWord = row.second[c];

            if (!DB::ComputableColumns.contains(DB::Columns(c))) {
                QCA::SecureArray word = Crypto::arrayXor(crypticWord.left(Crypto::N_BYTES - Crypto::M_BYTES), Crypto::generateS(ks, index));
                word.append(Crypto::arrayXor(Crypto::generateFki(Crypto::generateKi(kk, word), Crypto::generateS(ks, index++)), crypticWord.right(Crypto::M_BYTES)));
                plaintextRows.last().append(Crypto::postDecrypt(word.toByteArray(), kPrimePrime));
            } else {
                plaintextRows.last().append(Crypto::postDecrypt(crypticWord, kPrimePrime));
            }
        }
    }

    return plaintextRows;
}

QPair<DB::Word, QCA::SecureArray> DatabaseClient::encryptWordForSearch(DB::Word plainText)
{
    DB::Word ctxt = Crypto::preEncrypt(plainText, kPrimePrime.derivePublicKey());
    QCA::SecureArray cipherText(ctxt);
    QCA::SecureArray k = Crypto::generateKi(kk, cipherText.toByteArray().left(Crypto::N_BYTES-Crypto::M_BYTES));

    return QPair<DB::Word, QCA::SecureArray>(ctxt, k);
} //end encryptWordForSearch function
