/*
 * ES_MatchingSchema.h
 *
 *  Created on: 02 apr 2017
 *      Author: RedShy
 */
#ifndef SRC_ES_MATCHINGSCHEMA_H_
#define SRC_ES_MATCHINGSCHEMA_H_
#include<vector>

const unsigned * const initializeBlocksSwap2E(const std::vector<unsigned>& sig,
		const size_t& p)
{
	unsigned * const blocksig = new unsigned[sig.size()];
	unsigned marker = 0;
	blocksig[0] = 0;
	for (unsigned i = 1; i < sig.size(); ++i)
	{
		if (i % p == 0)
		{
			++marker;
		}
		blocksig[i] = marker;
	}
	return blocksig;
}


struct ES_MatchingSchema
{
		unsigned* sigma1;
		size_t sigma1l;

		unsigned* sigma2;
		size_t sigma2l;

		unsigned costValue;

		ES_MatchingSchema() :
				costValue(std::numeric_limits<unsigned int>::max()), sigma1l(0), sigma2l(
						0), sigma1(NULL), sigma2(NULL)
		{

		}

		ES_MatchingSchema(const std::vector<unsigned>&_sigma_1,
				const std::vector<unsigned>&_sigma_2) :
				costValue(0), sigma1l(
						_sigma_1.size()), sigma2l(_sigma_2.size())
		{
			sigma1 = new unsigned[_sigma_1.size()];
			std::iota(sigma1, sigma1 + _sigma_1.size(), 0);

			sigma2 = new unsigned[_sigma_2.size()];
			std::iota(sigma2, sigma2 + _sigma_2.size(), 0);


		}

		ES_MatchingSchema(const ES_MatchingSchema& m) :
				sigma1l(m.sigma1l), sigma2l(m.sigma2l), costValue(m.costValue)
		{
			sigma1 = new unsigned[sigma1l];
			std::copy(m.sigma1, m.sigma1 + sigma1l, sigma1);

			sigma2 = new unsigned[sigma2l];
			std::copy(m.sigma2, m.sigma2 + sigma2l, sigma2);
		}

		void shuffle() const
		{
			std::random_shuffle(sigma1, sigma1 + sigma1l);
			std::random_shuffle(sigma2, sigma2 + sigma2l);
		}

		void swap2() const
		{
			//Perform a single, simple swap of two indices for every vector

			//first vector
			unsigned i_1 = rand() % sigma1l;
			unsigned i_2 = rand() % sigma1l;

			unsigned temp = sigma1[i_1];
			sigma1[i_1] = sigma1[i_2];
			sigma1[i_2] = temp;

//			std::cout << "FIRST VECTOR: i_1=" << i_1 << " i_2=" << i_2 << "\n";

			//second vector
			i_1 = rand() % sigma2l;
			i_2 = rand() % sigma2l;

			temp = sigma2[i_1];
			sigma2[i_1] = sigma2[i_2];
			sigma2[i_2] = temp;

//			std::cout << "SECOND VECTOR: i_1=" << i_1 << " i_2=" << i_2 << "\n";

		}

		void swap2_enhanced(const unsigned * const blocksig1, const unsigned * const blocksig2) const
		{
			//Perform a single, simple swap of two indices for every vector

			//first vector
			unsigned i_1 = rand() % sigma1l;
			unsigned i_2 = rand() % sigma1l;

			//if they are the same don't do anything. This for maintaining good mutator's properties
			if(i_2 != i_1)
			{
				while(blocksig1[i_1] == blocksig1[i_2])
				{
					i_2 = rand() % sigma1l;
				}
			}

			unsigned temp = sigma1[i_1];
			sigma1[i_1] = sigma1[i_2];
			sigma1[i_2] = temp;

//			std::cout << "FIRST VECTOR: i_1=" << i_1 << " i_2=" << i_2 << "\n";

			//second vector
			i_1 = rand() % sigma2l;
			i_2 = rand() % sigma2l;

			//if they are the same don't do anything. This for maintaining good mutator's properties
			if(i_2 != i_1)
			{
				while(blocksig2[i_1] == blocksig2[i_2])
				{
					i_2 = rand() % sigma2l;
				}
			}

			temp = sigma2[i_1];
			sigma2[i_1] = sigma2[i_2];
			sigma2[i_2] = temp;

//			std::cout << "SECOND VECTOR: i_1=" << i_1 << " i_2=" << i_2 << "\n";

		}

		void swap2(const unsigned n) const
		{
			//Perform multiple simple swap of two indices for every vector
			for (unsigned i = 0; i < n; ++i)
			{
				//first vector
				unsigned i_1 = rand() % sigma1l;
				unsigned i_2 = rand() % sigma1l;

				unsigned temp = sigma1[i_1];
				sigma1[i_1] = sigma1[i_2];
				sigma1[i_2] = temp;

				//second vector
				i_1 = rand() % sigma2l;
				i_2 = rand() % sigma2l;

				temp = sigma2[i_1];
				sigma2[i_1] = sigma2[i_2];
				sigma2[i_2] = temp;
			}
		}

		void swap3() const
		{
			//first vector
			unsigned i_1 = rand() % sigma1l;
			unsigned i_2 = rand() % sigma1l;

			while (i_2 == i_1)
			{
				i_2 = rand() % sigma1l;
			}

			unsigned i_3 = rand() % sigma1l;

			while (i_3 == i_2 || i_3 == i_1)
			{
				i_3 = rand() % sigma1l;
			}

			unsigned temp1 = sigma1[i_1];
			unsigned temp2 = sigma1[i_2];
			unsigned temp3 = sigma1[i_3];
			sigma1[i_3] = temp1;
			sigma1[i_1] = temp2;
			sigma1[i_2] = temp3;

			//second vector
			i_1 = rand() % sigma2l;
			i_2 = rand() % sigma2l;

			while (i_2 == i_1)
			{
				i_2 = rand() % sigma2l;
			}

			i_3 = rand() % sigma2l;

			while (i_3 == i_2 || i_3 == i_1)
			{
				i_3 = rand() % sigma2l;
			}

			temp1 = sigma2[i_1];
			temp2 = sigma2[i_2];
			temp3 = sigma2[i_3];
			sigma2[i_3] = temp1;
			sigma2[i_1] = temp2;
			sigma2[i_2] = temp3;

		}

		void scramble() const
		{
			//first vector
			unsigned i_1 = rand() % sigma1l;
			unsigned i_2 = rand() % sigma1l;

			while (i_2 < i_1)
			{
				i_2 = rand() % sigma1l;
			}

			std::random_shuffle(sigma1 + i_1, sigma1 + i_2 + 1);

			//second vector
			i_1 = rand() % sigma2l;
			i_2 = rand() % sigma2l;

			while (i_2 < i_1)
			{
				i_2 = rand() % sigma2l;
			}

			std::random_shuffle(sigma2 + i_1, sigma2 + i_2 + 1);
		}

		void inversion() const
		{
			//first vector
			unsigned i_1 = rand() % sigma1l;
			unsigned i_2 = rand() % sigma1l;

			while (i_2 < i_1)
			{
				i_2 = rand() % sigma1l;
			}

			std::reverse(sigma1 + i_1, sigma1 + i_2 + 1);

			//second vector
			i_1 = rand() % sigma2l;
			i_2 = rand() % sigma2l;

			while (i_2 < i_1)
			{
				i_2 = rand() % sigma2l;
			}

			std::reverse(sigma2 + i_1, sigma2 + i_2 + 1);
		}

		void translocation() const
		{
			//first vector
			unsigned i_1 = rand() % sigma1l;
			unsigned i_2 = rand() % sigma1l;
			unsigned i_3 = rand() % sigma1l;

			while (i_2 < i_1)
			{
				i_2 = rand() % sigma1l;
			}

			while (i_3 < i_2)
			{
				i_3 = rand() % sigma1l;
			}

			std::rotate(sigma1 + i_1, sigma1 + i_2, sigma1 + i_3 + 1);

			//second vector
			i_1 = rand() % sigma2l;
			i_2 = rand() % sigma2l;
			i_3 = rand() % sigma2l;

			while (i_2 < i_1)
			{
				i_2 = rand() % sigma2l;
			}

			while (i_3 < i_2)
			{
				i_3 = rand() % sigma2l;
			}

			std::rotate(sigma1 + i_1, sigma1 + i_2, sigma1 + i_3 + 1);
		}

		void swap2_swap3() const
		{
			//first vector
			unsigned m = rand() % 2;
			if (m == 0)
			{
				//swap2
				unsigned i_1 = rand() % sigma1l;
				unsigned i_2 = rand() % sigma1l;

				unsigned temp = sigma1[i_1];
				sigma1[i_1] = sigma1[i_2];
				sigma1[i_2] = temp;
			}
			else
			{
				//swap3
				unsigned i_1 = rand() % sigma1l;
				unsigned i_2 = rand() % sigma1l;

				while (i_2 == i_1)
				{
					i_2 = rand() % sigma1l;
				}

				unsigned i_3 = rand() % sigma1l;

				while (i_3 == i_2 || i_3 == i_1)
				{
					i_3 = rand() % sigma1l;
				}

				unsigned temp1 = sigma1[i_1];
				unsigned temp2 = sigma1[i_2];
				unsigned temp3 = sigma1[i_3];
				sigma1[i_3] = temp1;
				sigma1[i_1] = temp2;
				sigma1[i_2] = temp3;
			}

			//second vector
			m = rand() % 2;
			if (m == 0)
			{
				//swap2
				unsigned i_1 = rand() % sigma2l;
				unsigned i_2 = rand() % sigma2l;

				unsigned temp = sigma2[i_1];
				sigma2[i_1] = sigma2[i_2];
				sigma2[i_2] = temp;
			}
			else
			{
				//swap3
				unsigned i_1 = rand() % sigma2l;
				unsigned i_2 = rand() % sigma2l;

				while (i_2 == i_1)
				{
					i_2 = rand() % sigma2l;
				}

				unsigned i_3 = rand() % sigma2l;

				while (i_3 == i_2 || i_3 == i_1)
				{
					i_3 = rand() % sigma2l;
				}

				unsigned temp1 = sigma2[i_1];
				unsigned temp2 = sigma2[i_2];
				unsigned temp3 = sigma2[i_3];
				sigma2[i_3] = temp1;
				sigma2[i_1] = temp2;
				sigma2[i_2] = temp3;
			}
		}

		bool operator<(const ES_MatchingSchema& m) const
		{
			return this->costValue < m.costValue;
		}

		ES_MatchingSchema& operator=(const ES_MatchingSchema& m)
		{
			costValue = m.costValue;

			if (sigma1l != m.sigma1l)
			{
				sigma1l = m.sigma1l;
				if (sigma1 != NULL)
				{
					delete[] sigma1;
				}
				sigma1 = new unsigned[sigma1l];
			}
			std::copy(m.sigma1, m.sigma1 + sigma1l, sigma1);

			if (sigma2l != m.sigma2l)
			{
				sigma2l = m.sigma2l;
				if (sigma2 != NULL)
				{
					delete[] sigma2;
				}
				sigma2 = new unsigned[sigma2l];
			}
			std::copy(m.sigma2, m.sigma2 + sigma2l, sigma2);
			return *this;
		}

		bool operator==(const ES_MatchingSchema& m) const
		{
			if (costValue != m.costValue || sigma1l != m.sigma1l
					|| sigma2l != m.sigma2l)
			{
				return false;
			}

			for (unsigned i = 0; i < sigma1l; ++i)
			{
				if (sigma1[i] != m.sigma1[i])
				{
					return false;
				}
			}

			for (unsigned i = 0; i < sigma2l; ++i)
			{
				if (sigma2[i] != m.sigma2[i])
				{
					return false;
				}
			}

			return true;
		}

		~ES_MatchingSchema()
		{
			delete[] sigma1;
			delete[] sigma2;
		}

		void print() const
		{
			std::cout << "sigma1= ";
			for (unsigned i = 0; i < sigma1l; ++i)
			{
				std::cout << sigma1[i] << " ";
			}
			std::cout << std::endl;

			std::cout << "sigma2= ";
			for (unsigned i = 0; i < sigma2l; ++i)
			{
				std::cout << sigma2[i] << " ";
			}
			std::cout << std::endl;
		}
};


#endif /* SRC_ES_MATCHINGSCHEMA_H_ */
