# My Flux APP Infra

Here we store the deployment configurations for a test application.

```bash
deploy/
├── base/
│   └── app/
│       ├── kustomization.yml
│       └── server.yml
└── overlays/
    ├── dev/
    │   ├── kustomization.yaml
    │   └── namespace.yml
    └── prd/
        ├── kustomization.yaml
        └── namespace.yml
```

* base/stores the common manifests for the application.
* overlay/ stores the configurations for each environment, dev and prd.
