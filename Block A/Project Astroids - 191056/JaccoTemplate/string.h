#pragma once

namespace Tmpl8
{
	// Ik zou al het gebruik van string vervangen met std::string. Dit is eigenlijk precies hetzelfde als deze class. Maar dan minder gevoelig voor 
	// memory leaks want het is een container. Het beheert namelijk de string waarnaar het verwijst met move semantics e.d. (Dat is wat je hier ook doet!)
	// https://stackoverflow.com/questions/3106110/what-is-move-semantics
	// Als je tijd hebt moet je hier in verdiepen, dan word je een stuk beter met memory management in C++.
	// Als je move semantics goed begrijpt dan begrijp hoe dingen als std::vector, std::string, std::unique_ptr, std::shared_ptr werken.
	// Nu weet ik niet of je die dingen mag gebruiken in dit projectje aangezien de meeste AAA devs de pesthekel hebben aan std containers...
	class String
	{
		private:
			const char* string;
		public:
			String(const char* string) :
				string(string)
			{};

			const char* GetString()
			{
				return string;
			}
			void StringFromIndex(int index)
			{
				char* newString = new char[GetLenght(index) + 1];
				
				int count = 0;

				for (int i = index; string[i] != '\0'; i++)
				{
					newString[count] = string[i];
					newString[count + 1] = '\0';

					count++;
				}

				string = newString;
			}

			bool operator==(const char* rhs)
			{
				int lenghtRhs = GetLenght(0, rhs);
				bool returnValue = false;

				for (int i = 0; string[i] != '\0'; i++)
				{
 					if (rhs[i] != string[i])
					{
						returnValue = false;
						break;
					}
					else if (string[i + 1] == '\0')
					{
						returnValue = true;
					}
				}

				return returnValue;
			}
			bool operator!=(const char* rhs)
			{
				return !operator==(rhs);
			}

			int GetLenght(int startIndex)
			{
				int lenght = 0;

				for (int i = 0; string[i] != '\0'; i++)
				{
					lenght++;
				}

				return lenght;
			}
			int GetLenght(int startIndex, const char* charToCount)
			{
				int lenght = 0;

				for (int i = 0; charToCount[i] != '\0'; i++)
				{
					lenght++;
				}

				return lenght;
			}
	};
}