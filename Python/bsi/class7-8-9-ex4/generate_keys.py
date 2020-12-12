import os

openssl = '~/Downloads/openssl-1.0.1p/apps/openssl'


def main():
    keys_length = ['1024', '2048', '4096']

    os.system('rm -r keys')

    if not os.path.isdir('keys'):
        os.system('mkdir keys')

    for key_length in keys_length:
        name_suffix = f'{key_length}.key'

        private_name = f'./keys/private.{name_suffix}'
        public_name = f'./keys/public.{name_suffix}'

        os.system(f'{openssl} genrsa -passout pass:student -out {private_name} {key_length}')
        os.system(f'{openssl} rsa -in {private_name} -passin pass:student -pubout -out {public_name}')


if __name__ == "__main__":
    main()
