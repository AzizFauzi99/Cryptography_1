#include "bits/stdc++.h"
using namespace std;

void menu(){
	cout << "==========================" << endl;
	cout << "MENU ENKRIPSI DAN DEKRIPSI" << endl;
	cout << "==========================" << endl << endl;
	cout << "1. Caesar Chipper" << endl;
	cout << "2. Vigenere Chipper" << endl;
	cout << "3. Rail Fence Chipper" << endl ;
	cout << "4. Super Enkripsi " << endl ;
	cout << "5. Keluar " << endl << endl;
}

string enkripsiCaesar(string text, int key)
{
    string result;
   
    for (int i = 0; i < text.length(); i++) {   
        if(isspace(text[i])){
			result += " ";
		}else if(text[i] >= 48 && text[i] <= 57){
			result += text[i];
		}
		else{
			// Encrypt Uppercase letters
			if (isupper(text[i])){
				result += char(int(text[i] + key - 65) % 26 + 65);
			}
			// Encrypt Lowercase letters
			else
				result += char(int(text[i] + key - 97) % 26 + 97);
		}
        
	}
    return result;
}

string dekripsiCaesar(string text, int key)
{
	key = 26 - key;
	string result;
 
    for (int i = 0; i < text.length(); i++) {
        
        if(isspace(text[i])){
			result += " ";			
		}else if(text[i] >= 48 && text[i] <= 57){
			result += text[i];
		}
		else{
			// Encrypt Uppercase letters
			if (isupper(text[i])){
				result += char(int(text[i] + key - 65) % 26 + 65);
			} 
			// Encrypt Lowercase letters
			else
				result += char(int(text[i] + key - 97) % 26 + 97);
		}
        
	}
    return result;
}


// Vigenere

// Fungsi ini menghasilkan kunci secara siklik hingga panjangnya tidak sama dengan panjang teks aslinya
string generateKey(string str, string key)
{
    int panjang = str.size();
 
    for (int i = 0; ; i++)
    {
		// Jika sudah sampe ujung, kembali lagi ke huruf awal
        if (i == panjang){
            i = 0;
            key.push_back(key[i]);
		}
        if (key.size() == str.size()){
            break;
        }
    }
    return key;
}
 
// This function returns the encrypted text generated with the help of the key
string enkripsiVigenere(string str, string key)
{
    string cipher_text;
 
    for (int i = 0; i < str.size(); i++)
    {
		if(isspace(str[i])){
			cipher_text.push_back(' ');
		}else if(str[i] >= 48 && str[i] <= 57){
			cipher_text.push_back(str[i]);
		}
		else{
			//converting in range 0-25
			char x = (str[i] + key[i]) % 26;
	 
			// convert into alphabets(ASCII)
			x += 'A';
	 
			cipher_text.push_back(x);
		}
        
    }
    return cipher_text;
}
 
// This function decrypts the encrypted text and returns the original text
string dekripsiVigenere(string cipher_text, string key)
{
    string orig_text;
 
    for (int i = 0 ; i < cipher_text.size(); i++)
    {
		if(isspace(cipher_text[i])){
			orig_text.push_back(' ');
		}else if(cipher_text[i] >= 48 && cipher_text[i] <= 57){
			orig_text.push_back(cipher_text[i]);
		}
		else{
			// converting in range 0-25
			char x = (cipher_text[i] - key[i] + 26) %26;
	 
			// convert into alphabets(ASCII)
			x += 'A';
			orig_text.push_back(x);
		}     
    }
    return orig_text;
}

// Rail Fence
string enkripsiRailFence(string text, int key)
{
    // create the matrix to cipher plain text
    // key = rows , length(text) = columns
    char rail[key][(text.length())];
 
    // filling the rail matrix to distinguish filled
    // spaces from blank ones
    for (int i=0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            rail[i][j] = '\n';
 
    // to find the direction
    bool dir_down = false;
    int row = 0, col = 0;
 
    for (int i=0; i < text.length(); i++)
    {
        // check the direction of flow
        // reverse the direction if we've just
        // filled the top or bottom rail
        if (row == 0 || row == key-1)
            dir_down = !dir_down;
 
        // fill the corresponding alphabet
        rail[row][col++] = text[i];
 
        // find the next row using direction flag
        dir_down?row++ : row--;
    }
 
    //now we can construct the cipher using the rail matrix
    string result;
    for (int i=0; i < key; i++)
        for (int j=0; j < text.length(); j++)
            if (rail[i][j]!='\n')
                result.push_back(rail[i][j]);
 
    return result;
}
 
// This function receives cipher-text and key and returns the original text after decryption
string dekripsiRailFence(string cipher, int key)
{
    // create the matrix to cipher plain text
    // key = rows , length(text) = columns
    char rail[key][cipher.length()];
 
    // filling the rail matrix to distinguish filled
    // spaces from blank ones
    for (int i=0; i < key; i++)
        for (int j=0; j < cipher.length(); j++)
            rail[i][j] = '\n';
 
    // to find the direction
    bool dir_down;
 
    int row = 0, col = 0;
 
    // mark the places with '*'
    for (int i=0; i < cipher.length(); i++)
    {
        // check the direction of flow
        if (row == 0)
            dir_down = true;
        if (row == key-1)
            dir_down = false;
 
        // place the marker
        rail[row][col++] = '*';
 
        // find the next row using direction flag
        dir_down?row++ : row--;
    }
 
    // now we can construct the fill the rail matrix
    int index = 0;
    for (int i=0; i<key; i++)
        for (int j=0; j<cipher.length(); j++)
            if (rail[i][j] == '*' && index<cipher.length())
                rail[i][j] = cipher[index++];
 
 
    // now read the matrix in zig-zag manner to construct
    // the resultant text
    string result;
 
    row = 0, col = 0;
    for (int i=0; i< cipher.length(); i++)
    {
        // check the direction of flow
        if (row == 0)
            dir_down = true;
        if (row == key-1)
            dir_down = false;
 
        // place the marker
        if (rail[row][col] != '*')
            result.push_back(rail[row][col++]);
 
        // find the next row using direction flag
        dir_down?row++: row--;
    }
    return result;
}

int main(){
	int n, submenu, k;
	string kalimat, hasil, keyword, ya;
	
	while(true){
		menu();
		cout << "Pilih Menu: ";
		cin >> n;
	
		if(n == 1){
			system("cls");
			do{
				cout << "CAESAR CHIPPER" << endl;
				cout << "1. Lakukan Enkripsi\n2. Lakukan Dekripsi" << endl;
				cout << "Pilih Option: ";
				cin >> submenu;
				
				cin.ignore();
				cout << "Masukkan Plaintext	: " ;	
				getline(cin, kalimat);
				
				if(submenu == 1){		
					cout << "Masukkan Kunci		: ";
					cin >> k;
					
					hasil = enkripsiCaesar(kalimat, k);
					cout << "Hasil Enkripsi		: " << hasil << endl;
				}else if(submenu == 2){
					
					cout << "Masukkan Kunci		: ";
					cin >> k;
					
					hasil = dekripsiCaesar(kalimat, k);
					cout << "Hasil Dekripsi		: " << hasil << endl;
				}else{
					cout << "Inputan Salah" << endl;
				}
				
				cout << "Coba Lagi (y/n)? ";
				cin >> ya;
			}while(ya == "y" || ya == "Y");
			
		}else if(n == 2){
			system("cls");
			do{
				cout << "VIGENERE CHIPPER" << endl;
				cout << "1. Lakukan Enkripsi\n2. Lakukan Dekripsi" << endl;
				cout << "Pilih Option: ";
				cin >> submenu;
				
				cin.ignore();
				cout << "Masukkan Plaintext	: " ;	
				getline(cin, kalimat);
				if(submenu == 1){
									
					cout << "Masukkan Key		: ";
					getline(cin, keyword);
					
					string key = generateKey(kalimat, keyword);
					hasil = enkripsiVigenere(kalimat, key);
					
					cout << "Hasil Enkripsi		: " << hasil << endl;
				}else if(submenu == 2){
									
					cout << "Masukkan Key		: ";
					getline(cin, keyword);
					
					string key = generateKey(kalimat, keyword);
					hasil = dekripsiVigenere(kalimat, key);
					
					cout << "Hasil Dekripsi		: " << hasil << endl;
				}else{
					cout << "Inputan Salah" << endl;
				}
				
				cout << "Coba Lagi (y/n)? ";
				cin >> ya;
			}while(ya == "y" || ya == "Y");
			
		}else if(n == 3){
			system("cls");
			do{
				cout << "RAIL FENCE CHIPPER" << endl;
				cout << "1. Lakukan Enkripsi\n2. Lakukan Dekripsi" << endl;
				cout << "Pilih Option: ";
				cin >> submenu;
				
				cin.ignore();
				cout << "Masukkan Plaintext	: " ;	
				getline(cin, kalimat);
				if(submenu == 1){
					
					cout << "Masukkan Kunci		: ";
					cin >> k;
					
					hasil = enkripsiRailFence(kalimat, k);
					cout << "Hasil Enkripsi		: " << hasil << endl;
				}else if(submenu == 2){
					
					cout << "Masukkan Kunci		: ";
					cin >> k;
					
					hasil = dekripsiRailFence(kalimat, k);
					cout << "Hasil Dekripsi		: " << hasil << endl;
				}else{
					cout << "Inputan Salah" << endl;
				}
				
				cout << "Coba Lagi (y/n)? ";
				cin >> ya;
			}while(ya == "y" || ya == "Y");

		}else if(n == 4){
			system("cls");
			do{
				cout << "SUPER ENKRIPSI/DEKRIPSI" << endl;
				cout << "1. Lakukan Enkripsi\n2. Lakukan Dekripsi" << endl;
				cout << "Pilih Option: ";
				cin >> submenu;
				
				cin.ignore();
				cout << "Masukkan Plaintext	: " ;	
				getline(cin, kalimat);
				if(submenu == 1){
					
					cout << "Masukkan Kunci	Number	: ";
					cin >> k;
					cin.ignore();
					cout << "Masukkan Kunci String	: ";
					getline(cin, keyword);
					
					hasil = enkripsiCaesar(kalimat, k);
					
					string key = generateKey(hasil, keyword);
					hasil = enkripsiVigenere(hasil, key);
					
					hasil = enkripsiRailFence(hasil, k);
					
					//cout << "Hasil Super Enkripsi	: " << endl;
					cout << "Hasil Enkripsi		: " << hasil << endl << endl;
				}else if(submenu == 2){
					
					cout << "Masukkan Kunci	Number	: ";
					cin >> k;
					cin.ignore();
					cout << "Masukkan Kunci String	: ";
					getline(cin, keyword);
					
					hasil = dekripsiRailFence(kalimat, k);
					
					string key = generateKey(hasil, keyword);
					hasil = dekripsiVigenere(hasil, key);
					
					hasil = dekripsiCaesar(hasil, k);
					
					//cout << "Hasil Super Dekripsi	: " << endl;
					cout << "Hasil Dekripsi		: " << hasil << endl << endl;
				}else{
					cout << "Inputan Salah" << endl;
				}
				
				cout << "Coba Lagi (y/n)? ";
				cin >> ya;
			}while(ya == "y" || ya == "Y");
		}else if(n == 5){
			break;
		}
		else{
			cout << "Masukkan Anda Salah, Silahkan Coba Lagi" << endl;
		}
	}
	
	
}
