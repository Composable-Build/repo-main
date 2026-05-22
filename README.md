# repo-main

![build](https://github.com/Composable-Build/repo-main/actions/workflows/integration.yml/badge.svg)

Charge les libs via `dlopen` et exécute les binaires. Affiche nom + version de chaque composant.

## Run local (après build des autres repos)
```bash
bash scripts/run_local.sh
```
## Forcer l'échec des tests
Dans `tests/test_config.h`, passer `TEST_SHOULD_FAIL` à `1`.
