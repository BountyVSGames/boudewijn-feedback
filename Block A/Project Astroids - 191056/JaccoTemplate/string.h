#pragma once

namespace Tmpl8
{
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