build:
	@clear
	@echo "[*] Make Generation"
	@cmake -S . -B bin
	@echo "[*] Compiling Program"
	@cmake --build bin
	@echo "[+] Task Done!"

install:
	@clear
	@sudo rm -rf bin /usr/local/bin/zprobe-cli /usr/lib/libprober.so
	@echo -e "[*] Make Generation"
	@cmake -S . -B bin
	@echo "[*] Compiling Program"
	@sudo .venv/bin/cmake --install bin
	@echo "[+] Task Done!"

run:
	@clear
	@bin/zprobe-cli

clean:
	@clear
	@rm -rf bin Debug Release
	@echo "[+] Cleaned"
	@echo -e "[+] Task Done!\n"
