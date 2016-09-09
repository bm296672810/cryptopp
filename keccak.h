// keccak.h - written and placed in the public domain by Wei Dai

//! \file keccak.h
//! \brief Classes for Keccak message digests
//! \details The Keccak classes use F1600 and XOF byte 0x80, which is effectively
//!   the behavior specified by NIST at round three of the selection process. If you
//!   desire FIPS 202 behavior, then use SHA3 classes.
//! \details Keccak will likely change in the future to accomodate extensibility of the
//!   round function and the XOF functions.
//! \details Perform the following to specify a different digest size. It will use F1600 and 0x80.
//! <pre>Keccack_192 : public Keccack
//! \sa <a href="http://en.wikipedia.org/wiki/Keccak">Keccak</a>

#ifndef CRYPTOPP_KECCAK_H
#define CRYPTOPP_KECCAK_H

#include "cryptlib.h"
#include "secblock.h"

NAMESPACE_BEGIN(CryptoPP)

//! \class Keccak
//! \brief Keccak message digest base class
//! \details The Keccak classes use F1600 and XOF byte 0x80, which is effectively
//!   the behavior specified by NIST at round three of the selection process. If you
//!   desire FIPS 202 behavior, then use SHA3 classes.
//! \details Keccak will likely change in the future to accomodate extensibility of the
//!   round function and the XOF functions.
//! \details Perform the following to specify a different digest size. The class will use F1600, 0x80,
//!   and a new vaue for <tt>r()</tt> (which will be <tt>200-2*24 = 152</tt>).
//!   <pre>  Keccack_192 : public Keccack
//!   {
//!     public:
//!       CRYPTOPP_CONSTANT(DIGESTSIZE = 24)
//!       Keccack_192() : Keccack(DIGESTSIZE) {}
//!   };
//!   </pre>
//!
class Keccak : public HashTransformation
{
public:
	//! \brief Construct a Keccak
	//! \param digestSize the digest size, in bytes
	//! \details Keccak is the base class for Keccak_224, Keccak_256, Keccak_384 and Keccak_512.
	//!   Library users should construct a derived class instead, and only use Keccak
	//!   as a base class reference or pointer.
	Keccak(unsigned int digestSize) : m_digestSize(digestSize) {Restart();}
	unsigned int DigestSize() const {return m_digestSize;}
	std::string AlgorithmName() const {return "Keccak-" + IntToString(m_digestSize*8);}
	unsigned int OptimalDataAlignment() const {return GetAlignmentOf<word64>();}

	void Update(const byte *input, size_t length);
	void Restart();
	void TruncatedFinal(byte *hash, size_t size);

protected:
	inline unsigned int r() const {return 200 - 2 * m_digestSize;}

	FixedSizeSecBlock<word64, 25> m_state;
	unsigned int m_digestSize, m_counter;
};

//! \class Keccak_224
//! \brief Keccak-224 message digest
class Keccak_224 : public Keccak
{
public:
	CRYPTOPP_CONSTANT(DIGESTSIZE = 28)

	//! \brief Construct a Keccak-224 message digest
	Keccak_224() : Keccak(DIGESTSIZE) {}
	CRYPTOPP_CONSTEXPR static const char *StaticAlgorithmName() {return "Keccak-224";}
};

//! \class Keccak_256
//! \brief Keccak-256 message digest
class Keccak_256 : public Keccak
{
public:
	CRYPTOPP_CONSTANT(DIGESTSIZE = 32)

	//! \brief Construct a Keccak-256 message digest
	Keccak_256() : Keccak(DIGESTSIZE) {}
	CRYPTOPP_CONSTEXPR static const char *StaticAlgorithmName() {return "Keccak-256";}
};

//! \class Keccak_384
//! \brief Keccak-384 message digest
class Keccak_384 : public Keccak
{
public:
	CRYPTOPP_CONSTANT(DIGESTSIZE = 48)

	//! \brief Construct a Keccak-384 message digest
	Keccak_384() : Keccak(DIGESTSIZE) {}
	CRYPTOPP_CONSTEXPR static const char *StaticAlgorithmName() {return "Keccak-384";}
};

//! \class Keccak_512
//! \brief Keccak-512 message digest
class Keccak_512 : public Keccak
{
public:
	CRYPTOPP_CONSTANT(DIGESTSIZE = 64)

	//! \brief Construct a Keccak-512 message digest
	Keccak_512() : Keccak(DIGESTSIZE) {}
	CRYPTOPP_CONSTEXPR static const char *StaticAlgorithmName() {return "Keccak-512";}
};

NAMESPACE_END

#endif
