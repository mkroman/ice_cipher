require 'spec_helper'

describe ICE::Cipher do
  describe "minimal instance" do
    subject { ICE::Cipher.new 0 }

    it "should have key size of 8" do
      expect(subject.key_size).to eq 8
    end

    it "should have a block size of 8" do
      expect(subject.block_size).to eq 8
    end

    it "should be able to set a key" do
      result = (subject.key = "12345678")

      expect(result).to eq "12345678"
    end
  end

  describe "instance with a key" do
    subject do
      ICE::Cipher.new(0).tap do |this|
        this.key = "12345678"
      end
    end

    context "input text length is divisible by 8" do
      let :encrypted_text do
        "\xE5\x03[a\xA2\x9D`\xE5".force_encoding('binary')
      end

      it "should be able to encrypt text" do
        cipher_text = subject.encrypt "hello..."

        expect(cipher_text).to eq encrypted_text
      end

      it "should be able to decrypt text" do
        plain_text = subject.decrypt encrypted_text

        expect(plain_text).to eq "hello..."
      end
    end
  end
end
