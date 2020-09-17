<template>
  <div class="login--containner">
    <el-form class="login-form" :model="loginForm" :rules="loginRules">

      <h3>Login Form</h3>

      <el-form-item prop="username">
        <el-input type="text" v-model="loginForm.username" autocomplete="on"
        />
      </el-form-item>

      <el-tooltip v-model="capsToolTip" content="大写锁定已打开" placement="right" manual>
        <el-form-item prop="password">
          <el-input type="text" v-model="loginForm.password" autocomplete="on" 
            @keyup.native="checkCapslock" 
            @blur="capsToolTip = false"
            @keyup.enter.native="handleLogin"
          />
        </el-form-item>
      </el-tooltip>

      <el-button type="primary" @click.native.prevent="handleLogin">Login</el-button>

      <el-button type="info" @click="registerDialogVisible = true">未注册？ 点击注册</el-button>

    </el-form>

    <el-dialog title="register" :visible.sync="registerDialogVisible">
      <el-form class="register-form" :model="registerForm" :rules="registerRules">
        
        <el-radio v-model="registerForm.role" label="1">租客</el-radio>
        <el-radio v-model="registerForm.role" label="2">客服</el-radio>

        <el-form-item prop="username" label="用户名">
          <el-input type="text" v-model="registerForm.username" autocomplete="on"
          />
        </el-form-item>

        <el-form-item prop="password" label="密码">
          <el-input type="text" v-model="registerForm.password" autocomplete="on"
          />
        </el-form-item>

      </el-form>

      <div>
        <el-button type="primary" @click="registerDialogVisible = false">取 消</el-button>
        <el-button type="primary" @click="handleRegister">注 测</el-button>
      </div>
    </el-dialog>
  </div>
</template>

<script>
  import { addDynamicRoutes } from '@/utils/router'

  export default {
    data() {
      return {
        loginForm: {
          username: 'zhijian',
          password: '123456',
        },
        loginRules: {
          // TODO
        },
        registerForm: {
          username: '',
          password: '',
          role: '1',
        },
        registerRules: {
          // TODO
        },
        capsToolTip: false,
        registerDialogVisible: false,
      }
    },
    methods: {
      checkCapslock(e) {
        const { key } = e
        this.capsTooltip = key && key.length === 1 && (key >= 'A' && key <= 'Z')
      },
      handleLogin() {
        this.postRequest('/account/login', this.loginForm).then(resp => {
          if (resp) {
            // console.log(resp)
            sessionStorage.setItem('username', resp.username)
            sessionStorage.setItem('role', resp.role)
            this.$router.push('/home')
          }
        })
      },
      handleRegister() {
        // $TODO: AUTO LOGIN
        // this.getRequest('/tenant', this.loginForm, { test: "test" }).then(resp => {
        //   console.log(resp)
        // })
      }
    }
  }
</script>