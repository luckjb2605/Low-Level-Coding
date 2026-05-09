// Generate random number and ask for guesses.
// Give feedback if number is gt or lt.

#include <iostream>
#include <random>

int generateRandomInt(void)
{
  static std::random_device randomDevice; // Random number from hardware (?)
  static std::mt19937 gen(randomDevice()); // Mersenne Twister engine
  static std::uniform_int_distribution<> dist(1, 100);
  return dist(gen);
}

int getGuess(void)
{
  int guess;
  std::cout << "Guess a number: ";
  std::cin >> guess;
  return guess;
}

int main(void)
{
  int randomNumber = generateRandomInt();
  int guess;

  while(true)
  {
    guess = getGuess();
    
    if (guess == 0)
    {
      std::cout << "Leaving.";
      return 0;
    }

    if (guess == randomNumber)
    {
      std::cout << "That's right! "
      << "The number was: "
      << randomNumber
      << std::endl;
      return 0;
    }

    if (guess < randomNumber)
    {
      std::cout << "Bigger!\n";
    }

    if (guess > randomNumber)
    {
      std::cout << "Smaller!\n";
    }
  }
}