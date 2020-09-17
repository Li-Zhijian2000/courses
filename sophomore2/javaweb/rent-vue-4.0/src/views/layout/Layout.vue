<template>
  <div style="height: 100%; width: 100%;">
      <div><NavMenu /></div>
      <div class="v3-main" 
        :style="{'margin-left': isNavMenuOpen ? '200px': '64px'}">
        <div class="v3-header"> <Header /> </div>
        <div class="v3-tabs"> <TopNav /> </div>
        <div><AppMain /></div>
        <!-- <a class="v3-content-main">
          <keep-alive :include="navTagIndexs">
            <router-view></router-view>
          </keep-alive>
        </el-main> -->
      </div>
  </div>
</template>
<script>
import { mapGetters, mapState } from 'vuex'
import NavMenu from './components/NavMenu'
import Header from './components/Header'
import TopNav from './components/TopNav'
import AppMain from './components/AppMain'
import { menu } from '@/config/menu-config'
export default {
  name: 'Layout',
  components: {
    NavMenu, Header, TopNav, AppMain
  },
  computed: {
    ...mapGetters(['navTagIndexs']),
    ...mapState(['isNavMenuOpen'])
  },
  created() {
    console.log(menu)
  }
}
</script>

<style scoped>
.v3-header {
  height: 40px;
  border-bottom: 1px solid #eee;
  background: #fff
}
.v3-main {
  margin-left: 200px;
}
.v3-content-main {
  background: #fff;
  margin: 10px;
}
.v3-tabs {
  background: #fff
}
</style>