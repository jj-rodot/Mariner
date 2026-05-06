# Security Policy

## Supported Versions

| Version | Supported |
|---|---|
| `main` | Yes |
| All others | No |

Only the current `main` branch receives security fixes. Older tags or forks are not maintained.

## Reporting a Vulnerability

Do not open a public issue for security vulnerabilities. Public disclosure before a fix is available puts all users at risk.

Report privately via GitHub's [Security Advisories](https://github.com/jj-rodot/Mariner/security/advisories/new) feature.

Include as much of the following as possible:

- A clear description of the vulnerability
- The component or subsystem affected (e.g. shader compilation, asset loading, IPC)
- Steps to reproduce or a minimal proof-of-concept
- The environment you reproduced it on (OS version, compiler, architecture)
- Potential impact or attack surface

You will receive an acknowledgement within 7 days. If the vulnerability is confirmed, a fix will be prioritised based on severity.

## Scope

Mariner is a native desktop application and game engine. The following are considered in scope:

- Memory safety issues (buffer overflows, use-after-free, etc.)
- Arbitrary code execution via asset or shader loading
- Privilege escalation on the host system
- Unsafe handling of untrusted input

The following are out of scope:

- Vulnerabilities in vendored third-party libraries (bgfx, bimg, bx, GLFW) — report these upstream
- Issues only reproducible on unsupported platforms
- Build system issues with no security impact

## Disclosure Policy

Once a fix is available and released, the vulnerability will be disclosed publicly via the GitHub Security Advisories page. Credit will be given to the reporter unless anonymity is requested.