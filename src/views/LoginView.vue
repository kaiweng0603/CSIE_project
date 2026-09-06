<template>
  <div class="login-page">
    <div class="login-card">
      <h1>IBEET Cloud Storage</h1>

      <p class="subtitle">Login to your account</p>

      <v-text-field
        v-model="email"
        label="Email"
        prepend-inner-icon="mdi-email"
        variant="outlined"
        class="input"
      />

      <v-text-field
        v-model="password"
        label="Password"
        prepend-inner-icon="mdi-lock"
        type="password"
        variant="outlined"
        class="input"
      />

      <v-btn color="primary" size="large" block @click="login"> LOGIN </v-btn>

      <div class="register">
        Don't have an account?
        <span>REGISTER</span>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import { useRouter } from 'vue-router'

const router = useRouter()

const email = ref('')
const password = ref('')

function login() {
  router.push('/home')
}
</script>

<style scoped>
.login-page {
  min-height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
  background: #1f1f1f;
}

.login-card {
  width: 360px;
  padding: 35px;
  background: white;
  border-radius: 20px;
  box-shadow: 0 10px 30px rgba(0, 0, 0, 0.4);
}

h1 {
  text-align: center;
  font-size: 28px;
  margin-bottom: 8px;
  color: #111;
}

.subtitle {
  text-align: center;
  color: #888;
  margin-bottom: 30px;
}

.input {
  margin-bottom: 12px;
}

.register {
  text-align: center;
  margin-top: 25px;
  color: #333;
}

.register span {
  color: #1976d2;
  margin-left: 5px;
  cursor: pointer;
}
</style>
