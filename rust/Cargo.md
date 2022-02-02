# Cargo

카고(Cargo)는 러스트의 빌드시스템 및 패키지 매니저이다. yarn 이나 npm 같은 친구이다. 카고는 `Cargo.toml` 라는 toml(Tom’s Obvious, Minimal Language) 포맷을 이용해 애플리케이션의 명세를 표현한다.

> 기존의 package.json 과 같은 역할을 하는 것 같다.

## 새 프로젝트 만들기

cargo 의 `new` 를 이용해 새 프로젝트를 스캐폴딩 할 수 있다.

```bash
$ cargo new hello_cargo --bin
$ cd hello_cargo
```

> --bin 인자는 라이브러리가 아닌 실행 가능한 애플리케이션임을 나타내준다.

### Cargo.toml

package.json 과 유사하게 생겼다. package 에는 프로젝트에 대한 명세가 나타나있다.
아직은 없지만 [dependencies] 에는 애플리케이션에서 사용할 의존성을 명시할 수 있다.

> 러스트에서는 코드의 패키지를 크레이트(crate) 라고 불린다. 크레이트는 npm 생태계와 비슷한 것 같다. 그리고 필요한 의존성들을 [crates.io](https://crates.io/) 에서 살펴볼 수 있다.

> Cargo.toml 에는 여러가지 정보를 포함할 수 있는데. [Cargo book](https://doc.rust-lang.org/cargo/reference/manifest.html) 에서 확인할 수 있다.

```
[package]
name = "hello_cargo"
version = "0.1.0"
edition = "2021"

# See more keys and their definitions at https://doc.rust-lang.org/cargo/reference/manifest.html

[dependencies]
```

## 빌드하고 실행하기

Cargo 의 new 를 이용해 만든 프로젝트에는 `src/*` 에 애플리케이션 관련 실행 파일들이 들어있다. 그리고 `Cargo.toml` 은 `src/main.rs`를 실행가능한 기본파일로 바라본다.

### 빌드

`cargo build` 를 이용해 main.rs 를 빌드한다. 그러면 `target/*` 이라는 폴더가 생성된다.

```bash
$ cargo build
```

### 실행

그리고 `target/*` 에는 실행 가능한 바이너리 파일이 들어있다.
이 바이너리 파일을 실행하면 된다.

```bash
./target/debug/hello_cargo

Hello, world!
```

rust 는 빌드와 실행 단계를 나누었는데 실행할 때 불편할까봐 빌드 후 바로 실행하는 명령어를 기본으로 제공한다.

```bash
$ cargo run
```

위의 명령어를 입력하면 build 후 바로 바이너리 파일을 실행해준다.

### cargo check

만약 실행을 원하지 않고 '실행이 가능한지 여부' 만 판단하고 싶다면 다음 명령어를 통해 확인할 수 있다.

```bash
$ cargo check
```

`cargo check` 는 `cargo build` 보다 당연히 더 빠르다. 실행가능한 바이너리파일을 만들지 않기 때문이다.

### [Cargo Package Layout](https://doc.rust-lang.org/cargo/guide/project-layout.html?highlight=main.rs#package-layout)

Cargo 의 폴더구조이다.

```
.
├── Cargo.lock
├── Cargo.toml
├── src/
│   ├── lib.rs
│   ├── main.rs
│   └── bin/
│       ├── named-executable.rs
│       ├── another-executable.rs
│       └── multi-file-executable/
│           ├── main.rs
│           └── some_module.rs
├── benches/
│   ├── large-input.rs
│   └── multi-file-bench/
│       ├── main.rs
│       └── bench_module.rs
├── examples/
│   ├── simple.rs
│   └── multi-file-example/
│       ├── main.rs
│       └── ex_module.rs
└── tests/
    ├── some-integration-tests.rs
    └── multi-file-test/
        ├── main.rs
        └── test_module.rs
```

## 릴리즈 빌드

배포용 빌드(릴리즈 빌드)는 최적화가 필요할 것이다. 배포용 빌드는 별도 옵션을 추가하면된다.

```bash
$ cargo build --release
```

그러면 cargo 는 `target/release` 에 최적화된 릴리즈용 실행파일을 만들어준다.
