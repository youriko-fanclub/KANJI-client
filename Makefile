SIV3D_BASENAME := siv3d_v0.4.3_macOS
SIV3D_TEMPLATE_URL := https://siv3d.jp/downloads/Siv3D/$(SIV3D_BASENAME).zip

.DEFAULT_GOAL := help

init: ## Initialize sub modules and Siv3D libaries
	@git submodule update --init --recursive
	@wget -qO- "$(SIV3D_TEMPLATE_URL)" | tar -xv --strip-components 1 $(SIV3D_BASENAME)/include/ $(SIV3D_BASENAME)/lib/

build: ## Build and Open application
	@cd ./Game/KANJI && xcodebuild && open App/*.app

help: ## Display the help
	@echo "Usage:\n    make <command>"
	@echo ""
	@echo "Commands:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "    \033[36m%-20s\033[0m %s\n", $$1, $$2}'

.PHONY: init build help
