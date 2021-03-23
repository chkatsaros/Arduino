/* Include this header to implement a 4x3 or 4x4 Arduino keypad
 * using only 3 or 4 pins 
 * Use KeypadLessPins(rows, cols, pin1, pin2, pin3, 0) if 4x3 or KeypadLessPins(rows, cols, pin1, pin2, pin3, pin4) if 4x4
 * 
 * By Spark - Christos Katsaros
 */

class KeypadLessPins {

	private:
		int cols, rows, pin1, pin2, pin3, pin4;
		const int NADCm100[4] = {923,669,412,156};
		const int NADCp100[4] = {1123,869,612,356};
		const char key43[13] = {'1','4','7','*','2','5','8','0','3','6','9','#'};
		const char key44[17] = {'1','4','7','*','2','5','8','0','3','6','9','#', 'A','B','C','D'};
		int keyval43[3];
		int keyval44[4];
		int i, colp, val;

	public:
		KeypadLessPins(int rows, int cols, int pin1, int pin2, int pin3, int pin4) {
			this->rows = rows;
			this->cols = cols;
			this->pin1 = pin1;
			this->pin2 = pin2;
			this->pin3 = pin3;
			this->pin4 = pin4;
		}

		KeypadLessPins(int rows, int cols, int pin1, int pin2, int pin3) {
			this->rows = rows;
			this->cols = cols;
			this->pin1 = pin1;
			this->pin2 = pin2;
			this->pin3 = pin3;
		}

		char KeyPad() {
			
			scanKeypad();
		    
		    // key = 'N' for none

		    // 4x3 keypad
		    if (cols == 3) {
		    	// no input from keypad
			    if ((keyval43[0] + keyval43[1] + keyval43[2]) < 100) {
			        return 'N';
			    }
			    // a key was pressed
			    else {
			    	
			    	scanKeypad();

				    for (i = 0; i < cols; i++) {
				        
				        if (keyval43[i] > 100) {
				        	colp = i;
				        	val = keyval43[i];
				        	
				        	for (int j = 0; j < rows; j++) {
				        		// identify which key was pressed on the column
				            	if ((val >= NADCm100[j]) && (keyval43[i] <= NADCp100[j])) { 
				            		return key43[colp * rows + j];
				            		break;
				          		}
				        	}
				        }  
				    }
				}
			}
			// 4x4 keypad
			else if (cols == 4) {
				// no input from keypad
			    if ((keyval44[0] + keyval44[1] + keyval44[2] + keyval44[3]) < 100) {
			        return 'N';
			    }
			    // a key was pressed
			    else { 
			        delay(10);

			    	scanKeypad();

				    for (i = 0; i < cols; i++) {
				        if (keyval44[i] > 100) {
				        	colp = i;
				        	val = keyval44[i];
				        	
				        	for (int j = 0; j < rows; j++) {
				        		// identify which key was pressed on the column
				            	if ((val >= NADCm100[j]) && (keyval44[i] <= NADCp100[j])) { 
				            		return key44[colp * rows + j];
				            		break;
				          		}
				        	}
				        }  
				    }
				}
			}
		}

		// read analog keyboard input
		char scanKeypad() {
	 		
	 		keyval43[0] = keyval44[0] = analogRead(pin1);
	    	keyval43[1] = keyval44[1] = analogRead(pin2);
	    	keyval43[2] = keyval44[2] = analogRead(pin3);
	    	if (cols == 4) {
	    		keyval44[3]= analogRead(pin4);
	    	}
		}
};

