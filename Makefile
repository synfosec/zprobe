build:
	@clear
	@rm -rf bin lib/whois
	@echo -e "[*] Make Generation\n"
	@cmake -S . -B bin
	@echo -e "\n[*] Downloading misc tools\n"
	@git clone -q "https://github.com/rfc1036/whois.git" lib/whois
	@echo "whois"
	@echo -e "\n[*] Compiling Program\n"
	@cd lib/whois; make
	@echo ""
	@cmake --build bin
	@mv lib/whois/whois bin
	@echo -e "\n[+] Task Done!\n"

install:
	@clear
	@sudo rm -rf bin lib/whois /usr/local/bin/zprobe-cli /usr/lib/libprober.so /usr/local/bin/whois
	@echo -e "[*] Make Generation\n"
	@cmake -S . -B bin
	@echo -e "\n[*] Downloading misc tools\n"
	@git clone -q "https://github.com/rfc1036/whois.git" lib/whois
	@echo "whois"
	@echo -e "\n[*] Compiling Program\n"
	@cd lib/whois; make
	@echo ""
	@sudo cmake --install bin
	@sudo mv lib/whois/whois /usr/local/bin
	@echo -e "\n[+] Task Done!\n"

run:
	@clear
	@bin/zprobe-cli

clean:
	@clear
	@rm -rf bin Debug Release lib/whois /usr/local/bin/zprobe-cli /usr/lib/libprober.so /usr/local/bin/whois
	@echo "[+] Cleaned"
	@echo -e "[+] Task Done!\n"
