# Process synchronization using semaphores
Let's imagine factory where item is produced whitch is consist of two elements Y and Z. In factory work N + M + P robots (processes) 

- N robots specialize in production elements Y and after producing they put it on assembly line (buffor) BY 
- M robots specialize in production elements Z and after producing they put it on assembly line (buffor) BZ 
- P robots gathers and pairs elements from assembly lines BY and BZ and final product YZ is finished 
- Assume that elements Y and Z are natural numbers less then 10 and pairing Y and Z is operaration that produces number YZ with value Y*10+Z
- Assume that on assemby line there could be at once max 5 elements  
- Production shoud be finished after building 10 products YZ
- Pairing robots first gests elemnt from queque Y and later from queque Z and paired product YZ prints on standard output. If any of these queques is empty robot waits for element
- Symulate robots working time by sleeping proceses with ranom value from:
- <1, R> for processes producing Y,
- <1, S> for processes producing Z,
- Values M, N, P, R, S i T should be cofigured after start



