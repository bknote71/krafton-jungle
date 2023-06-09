# 4월 5일 TIL (Today I Learned)

## JWT (Json Web Token) 인증 방식

: 기존 인증 방식인 세션의 단점을 극복하고 좀 더 확장성 있는 서버 구현을 위해 나타난 인증 방식

공식 사이트: https://jwt.io/

### Session 이란?
- 연결 컨텍스트(Context)
- 그 중 Http Session 은 Http 상에서 클라이언트와 서버간의 연결 정보를 의미한다.

참고:  Context
- 특정 문맥에서의 정보
- 예: PCB(Process Control Block) : 프로세스를 관리하기 위해 필요한 정보

### Http Session
- Session 은 특정 세션 ID를 가지는 클라이언트만 사용할 수 있는 정보이다.
- 즉, 특정 세션 ID를 통해 세션 스토어에서 클라이언트 본인의 세션 정보를 가져온다.
- 이 세션에는 클라이언트의 다양한 정보를 담을 수 있게 된다.


### 세션 인증 방식

1. 클라이언트 to 서버
- username & password 전송 (form, ajax, ...)

2. 서버 측에서 인증 과정을 거친 후 세션에 "인증 정보" 를 저장한다.
- 인증 정보? 
    - 인증을 완료한 유저에 대한 유저 정보이다.

3. 인증 정보를 저장한 세션에 대한 ID를 Set-Cookie 헤더에 담아서 전달한다.
- 클라이언트가 Set-Cookie 헤더를 받으면 다음 요청부터 Cookie에 헤더로 전달된 값을 담아 요청하게 된다.

4. 클라이언트는 Cookie 에 Session ID 를 담아서 요청하게 된다.

5. 서버는 해당 세션 ID로 세션 정보를 가져와 세션에 있는 인증 정보를 꺼내서 클라이언트의 인증 여부를 검증할 수 있다.

### 세션 인증 방식의 단점?
- 세션은 "상태(state)" 를 서버 메모리에 저장한다.
- 만약 사용자가 매우 많은 상황에서 서버의 메모리를 많이 차지할 뿐만 아니라 서버 확장(Scale-out)하기도 매우 힘들어진다.
- 이런 세션 인증 방식의 단점을 보완하기 위해 JWT(Json Web Token) 이라는 인증 방식이 나왔다.

### JWT (Json Web Token)
- Json Web Token
- Json 형식의 데이터를 인코딩 및 암호화한 문자열 토큰이다.
- 웹 애플리케이션 간에 정보를 안전하게 전송하기 위한 토큰 기술

구성
1. Header(헤더)
- 알고리즘(alg), 타입(typ)
- 토큰의 유형과 암호화 알고리즘

2. Payload(페이로드)
- 클레임(Claim) 을 포함한다.
  - 쉽게 생각해서 토큰에 담는 메인 정보이다.
  - 3가지의 유형으로 나뉜다.

- 클레임 유형
  1. 등록된 클레임
     - 이미 정의된 클레임 
     - iss(토큰 발행자), exp(만료 시간), sub(토큰 제목, 주제), aud(토큰 대상자)
  2. 공개된 클레임
     -  사용자가 정의할 수 있는 클레임
     -  ex. userId = '~'
  
  3. 비공개 클레임
     - 공개되지 않는 클레임


3. Signature(서명)
- 암호화 알고리즘을 사용하여 서명을 만든다.
- Signature: HMAC-SHA256(Header + Payload + 시크릿 키)
### 암호화 과정
Base64(Header) + "." +
Base64(Payload) + "." + 
Base64(Signature)

- 디코딩한 시그니처 값과 디코딩한 header 와 payload 를 다시 HS256 알고리즘을 적용했을 때 값이 다르면 변한 것이다.
- 즉, 토큰을 중간에 변경하면 base64인코딩 및 해쉬 암호화 알고리즘 때문에 토큰 문자열이 완전히 달라지게 된다.

참고: 
- HMAC: 시크릿 키를 포함한 암호화 방식
- SHA256: 해쉬 함수 (복호화 X)
- HMAC-SHA256: 시크릿 키를 포함해서 해쉬 함수를 적용하는 방식


### JWT를 인증 방식에 어떻게 적용할 수 있을까?
- 인증이 완료된 유저의 간단한 정보를 JWT에 담아서 클라이언트와 서버간 통신에 이용할 수 있다.
- 거기다, 토큰이 중간에 변경되지 않았다는 것을 쉽게 검증할 수 있기 때문에, JWT를 보낸 클라이언트가 정상적인 토큰을 전달했는지를 쉽게 파악하고 전달된 토큰으로 인증이 된 클라이언트인지 알 수 있다.

인증 과정
1. 클라이언트 to 서버
- username & password 전송 (form, ajax, ...)

2. 서버 측에서 인증 과정을 거친 후 인증된 사용자 정보를 JWT 라는 토큰에 담아 응답(쿠키?)으로 전달한다.

3. 응답으로 전달된 토큰을 클라이언트에서 보관하고 있다가 다음 요청때부터 JWT 토큰을 요청에 담아 전달할 수 있다.

4. 서버는 JWT 의 특성을 사용하여 쉽게 인증 검증을 할 수 있다.
- Header, Payload, Signature를 디코딩 후 Header + Payload +  시크릿키를 HS256 해쉬 알고리즘을 적용 후 시그니처와 비교해서 검증할 수 있다.


### JWT 인증 방식의 단점 !!!

보안 이슈

1. JWT는 변환이 쉽다.
- 왜? 
  - Base64 인코딩: 바로 디코딩할 수 있다.
  - 즉 토큰을 중간에서 가로챈 뒤에 Base64 디코딩을 하면 헤더, 페이로드, 시그니처 값을 알 수 있게 된다.
- 변환이 쉽기 때문에 토큰에 유저의 민감한 정보를 넣어서는 안된다.
- 최소한의 정보만!
  
2. 시크릿 키 문제
- 브루트 포스 알고리즘을 통해 맞추기 쉬울 수 있다.
- 키를 매우 길게 설정하고 키를 잘 관리해야 한다.
- RSA 암호화(공개키/개인키)를 사용한다.
- 개인 키로 암호화해서 반환하고 검증 시에 공개 키로 열어보기

3. JWT 탈취
- 탈취하면 방법이 없고, 이를 사전에 방지하는 방법밖에 없다.
- 훔치기 어렵게 만들기: HttpOnly, Secure Cookie
- JWT 유효기간을 짧게 + refresh token 사용

근데 refresh token 역시 탈취당하면 어떻게 돼지?
- 앞으로 공부할 내용.


참고: request 시 Cookie vs Authorization 헤더에 담아서 보내는 차이
- Cookie: Set-Cookie 헤더를 통해서 jwt 토큰을 응답받으면 다음 요청부터 브라우저에서 자동으로 요청에 담아 전달한다.
- Authorization: 브라우저에서 jwt 토큰을 자동으로 전달하지 않기 때문에 좀 더 안전하고, 원하는 상황에만 토큰을 전달할 수 있게해서 CSRF attack을 예방할 수 있다. (하지만 일일히 코딩해야 하는 단점)

### 참고: CSRF(Cross Site Request Forgery) attack
- admin 관리자가 로그인 이후 자신의 이메일로온 하이퍼 링크가 있는 이미지를 클릭하게 된다면?
- 근데 이 하이퍼 링크의 주소가 admin 권한이 필요하고 서버의 중요한 기능을 수행하는 주소라면?
- admin 관리자는 권한이 있기 때문에 해당 리소스에 접근한 다음 관리자도 모른채 중요한 기능을 수행할 수 있게 된다.

공격을 막으려면?
1. Post 방식
- 하이퍼 링크(a tag)로 공격하지 못한다.

2. Referrer 검증
- request header에서 referrer 속성을 검증하여 차단한다,
- 같은 도메인 상에서 요청이 들어오지 않는다면 차단

3. CSRF Token
- 사용자 세션을 사용하여 사용자의 모든 요청에 대해 서버에서 검증하는 방식
- 로그인 시, 혹은 작업 화면 요청 시 CSRF Token을 생성하여 세션에 저장한다.
- 요청 페이지에 CSRF Token을 세팅(HTML Form)하여 특정 요청때마다 토큰을 전송할 수 있게 한다.
- 예: input tag type="hidden" name="_csrf" value="${CSRF_TOKEN}"
- CSRF Token을 쿠키로 저장하면 요청 시마다 자동으로 전달되기 때문에 보안상 취약하다. (사실상 의미가 없는 것 아닌가 생각해본다.)

### JWT에서 CSRF 공격 대응 방법
- Html Form 태그 CSRF Token
  - 근데 CSRF Token을 검증하기 위해서는 세션이 필요하긴 하다.
  - 이는 JWT 를 사용해도 완전히 세션을 사용하지 않을 수는 없다는 말이다.
- Authorization 헤더
  - 쿠키와 다르게 브라우저에서 자동으로 jwt 토큰을 요청할 때 전송하지 않게 한다.