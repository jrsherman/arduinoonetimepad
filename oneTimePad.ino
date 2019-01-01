#include <StandardCplusplus.h>
#include <serstream>
#include <avr/pgmspace.h>
// when the encrypt char has a key value of a that means there will be no shift in the output
//this is because a is the base shift of 0 letters to the right


// if using the whole table I think you would only have to wrap at 127
//otherwise no need

using namespace std;
// ascii is [97,122] for lowercase
//[65,90] uppercase
//
// <iostream> declares cout/cerr, but the application must define them
// because it's up to you what to do with them.
namespace std
{
  ohserialstream cout(Serial);
}
extern void more(void);
//n corresponds to the input message from 0-25 letters
//m corresponds to the key value from 0-25 letters therefore shifts to the right of the original
// from 0-25 shifts to the right and wrapping around once it hits 25 going back to 0 shift

//message+key then mod by 26 so it stays in the letter range and boom u have your cyphertext

/*

int wrap(int inputMessage, int key) {
	int hourHand;
	if(inputMessage < 0){
		int negMod = inputMessage%key;
		hourHand = key + negMod;
                if(negMod == 0){
                      hourHand = 0;
                 }
	}
	else {
	 hourHand = inputMessage%key;
	}
	return hourHand;
}
*/
int wrap(int inputMessageChar, int key) {
  int encryptedChar;
  if((inputMessageChar+key) < 0){ 
    encryptedChar = (((inputMessageChar+key)%26)+26)%26;
  }
  else {
   encryptedChar = (inputMessageChar+key)%26;//mod works on numbers exceeding the 25 in this case otherwise 
   //the remainder will be inputMessageChar+key. which works also if we are decrypting with a negative number not 
   // lower than 0
  }
  return encryptedChar;
}



/***********
 * Setup Serial at 57600 baud in monitor window
 * 
 */



void setup(void)
{
  
  
  randomSeed(analogRead(0)); // random seed changes with analog read
  Serial.begin(57600);
  int arraySize = 80;
  char key[arraySize]; //instantiate key
  int randNumber[arraySize];
  for(int i=0;i < arraySize; i++){
    randNumber[i] = random(0,26);//put random numbers between 0-25 into an array
  }
  
  //string toEncrypt =  "this is my first encryption";
  string toEncrypt =  "plaziosaur12";
  //demonstrates the ability to cout index of chars
  //cout << toEncrypt[26] << endl;
  //cout << toEncrypt.size() << endl;
  int stringSize = toEncrypt.size();
  
  char charArray[stringSize+1];

  for(int i = 0; i < stringSize; i++){
     charArray[i]  =  toEncrypt[i];
  }
  charArray[stringSize] = '\0';
  cout << endl;

  //we now have a char array of our string.
  cout << "Input Message: ";
  //char array is the original message
  for(int i = 0; i <= stringSize; i++)
    cout << charArray[i];
  cout << endl;
  //We have just displayed the input message by parsing through the string.
  
  


  
  //We now create a char array to hold the encrypt key
  cout << "Encrypt Key: ";
  //static_cast<char>()
  for(int i = 0; i < arraySize; i++){
    key[i] = randNumber[i]+'a'; // uses the already generated
    cout <<  key[i];
    // random numbers from 0-25 and assembles them into a key of chars
  }
  //We have just used the random opperation to assign random letter values
  //to each letter space needed.

  //We now create the encrypted message using the random key
  //we have just generated. 
  char encryptedArray[stringSize+1];//instantiate our encrypt array here
  for(int i = 0; i < arraySize; i++){
    if (charArray[i] >= 'a' && charArray[i] <='z')//if the letter in the message is 
    //equal to or between a and z
    //its looking at the char letter numbers i think
    //thus the wrap is where all the magic happens
      encryptedArray[i] = (wrap(charArray[i]-'a', key[i]-'a'))+'a'; 
      //we subtract the ascii a from the mix so we c
      //but shift it to the right by the key value
     else
       encryptedArray[i] = charArray[i];// leaving the spaces intact
       //or numbers this is validated
   //cout << key[i]-'a';
    //cout<< endl;
  }
  //we have just assigned values to a char array which we call encryptedArray
  //we can use the key to switch back and forth between cyphertext
  //and plain text
  cout << endl;

// the code braeks here for some reasdon
  
  cout << "Encrypted string: ";
    for(int i = 0; i < stringSize; i++){
      cout << encryptedArray[i];
      /*cout << key[i]-'a';
      cout << endl;*/
    }

  // IF YOU WANT TO DECRYPT given key and message unhash this
  /*
    string givenToDecrypt =  "Akelffu12!!";
  int stringSizeDecrypt = givenToDecrypt.size();
  char decryptArray[stringSize+1];
  for(int i = 0; i < stringSize; i++){
     encryptedArray[i]  =  givenToDecrypt[i];
  } 

  string givenKey =  "crxqfnrywcstpdms";
  int stringSizeKey = givenToDecrypt.size();
  char keyArray[stringSize+1];
  for(int i = 0; i < stringSize; i++){
     key[i]  =  givenKey[i];
  } */



    
//the thing we are doing to encypt is moving each letter by a random value
//to the right of the orignial message value.
//thus we use the key to ascertain by exactly how much we move the letter to the
//right
//since these are supposadly random shifted values it is pretty imposible
//to crack now to shift back we use the random key that was generated
//and shift the encrypted string back to the left to get the original message
  //we now turn cypher back into regular text
  char decryptedArray[stringSize+1];//we create a string to decrpt message
//we are making decrypt array here

  for(int i = 0; i < arraySize; i++){
    if (encryptedArray[i] >= 'a' && encryptedArray[i] <='z'){
      decryptedArray[i] = (wrap(encryptedArray[i]-'a', -((key[i])-'a')))+'a'; 
    // we are discounting the spaces which have value of 65 after take out ascii
    }
     else
       decryptedArray[i] = encryptedArray[i];  
  }
// its working except for the negative letters
    cout << endl;
  cout << "Decrypted string: ";
    for(int i = 0; i < stringSize; i++)
        cout << decryptedArray[i];
}
void loop(void)
{
}
